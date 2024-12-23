# Copyright (c) 2023 ACAL, National Cheng Kung University
# Copyright (c) 2022 Playlab, National Cheng Kung University
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met: redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer;
# redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution;
# neither the name of the copyright holders nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

FROM ubuntu:20.04

ARG UID=1000
ARG GID=1000
ARG USERNAME="user"
ARG TZ="Asia/Taipei"
ARG ARCH

ENV INSTALLATION_TOOLS apt-utils \
    curl \
    software-properties-common \
    wget

ENV DEVELOPMENT_PACKAGES python3.8 \
    python3-pip \
    python-is-python3 \
    clang-format

ENV TOOL_PACKAGES bash \
    dos2unix \
    git \
    locales \
    nano \
    tree \
    vim \
    sudo \
    gdb \
    zip \
    unzip \
    htop

ENV RENODE_PACKAGES policykit-1 \
    libgtk2.0-0 \
    screen \
    uml-utilities \
    gtk-sharp2 \
    libc6-dev \
    gcc \
    python3 \
    python3-pip

ENV USER ${USERNAME}
ENV TERM xterm-256color
ENV APT_KEY_DONT_WARN_ON_DANGEROUS_USAGE DontWarn

# install system packages
RUN apt-get -qq update && \
    apt-get -qq install ${INSTALLATION_TOOLS} && \
    # prerequisite - git
    add-apt-repository ppa:git-core/ppa && \
    # prerequisite - clang-format
    # ref: https://apt.llvm.org
    echo "deb http://apt.llvm.org/focal/ llvm-toolchain-focal main" | tee -a /etc/apt/sources.list && \
    echo "deb-src http://apt.llvm.org/focal/ llvm-toolchain-focal main" | tee -a /etc/apt/sources.list && \
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
    # start install
    apt-get -qq update && \
    apt-get -qq upgrade && \
    apt-get -qq install ${DEVELOPMENT_PACKAGES} ${TOOL_PACKAGES} ${RENODE_PACKAGES}

# install python libraries
COPY ./config/requirements.txt /tmp/requirements.txt
RUN pip3 install -r /tmp/requirements.txt && \
    rm /tmp/requirements.txt

# install chisel3 with verilator 4.202
# ref: https://github.com/chipsalliance/chisel3/blob/master/SETUP.md
RUN apt-get -qq install default-jdk && \
    echo "deb https://repo.scala-sbt.org/scalasbt/debian all main" | sudo tee /etc/apt/sources.list.d/sbt.list && \
    echo "deb https://repo.scala-sbt.org/scalasbt/debian /" | sudo tee /etc/apt/sources.list.d/sbt_old.list && \
    curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | sudo apt-key add && \
    apt-get -qq update && \
    apt-get -qq install sbt && \
    apt-get -qq install git make autoconf g++ flex bison && \
    git clone -c advice.detachedHead=false --branch "v4.202" --depth 1 "https://github.com/verilator/verilator.git" /tmp/verilator && \
    cd /tmp/verilator && \
    unset VERILATOR_ROOT && \
    autoconf && \
    ./configure > /dev/null 2>&1 && \
    make -j $(nproc) > /dev/null 2>&1 && \
    make install > /dev/null 2>&1 && \
    rm -r /tmp/verilator

# CFU Playground - RISC-V toolchain
RUN wget -q -c "https://static.dev.sifive.com/dev-tools/freedom-tools/v2020.08/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14.tar.gz" -O "/tmp/riscv-tool.tar.gz" && \
    tar xzvf "/tmp/riscv-tool.tar.gz" -C "/tmp/" && \
    mv "/tmp/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14" "/usr/local/" && \
    rm "/tmp/riscv-tool.tar.gz"
ENV PATH "${PATH}:/usr/local/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14/bin"

# setup time zone
RUN ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone

# add support of locale zh_TW
RUN sed -i 's/# en_US.UTF-8/en_US.UTF-8/g' /etc/locale.gen && \
    sed -i 's/# zh_TW.UTF-8/zh_TW.UTF-8/g' /etc/locale.gen && \
    sed -i 's/# zh_TW BIG5/zh_TW BIG5/g' /etc/locale.gen && \
    locale-gen && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    update-locale LANG=en_US.UTF-8 && \
    update-locale LC_ALL=en_US.UTF-8
ENV LC_ALL en_US.UTF-8

# add non-root user account
RUN groupadd -o -g ${GID} ${USERNAME} && \
    useradd -u ${UID} -m -s /bin/bash -g ${GID} ${USERNAME} && \
    echo "${USERNAME} ALL = NOPASSWD: ALL" > /etc/sudoers.d/${USERNAME} && \
    chmod 0440 /etc/sudoers.d/${USERNAME} && \
    passwd -d ${USERNAME}

# add scripts and setup permissions
COPY --chown=${UID}:${GID} ./scripts/.bashrc /home/${USERNAME}/.bashrc
COPY --chown=${UID}:${GID} ./scripts/start.sh /docker/start.sh
COPY --chown=${UID}:${GID} ./scripts/login.sh /docker/login.sh
COPY --chown=${UID}:${GID} ./scripts/startup.sh /usr/local/bin/startup
RUN dos2unix -ic "/home/${USERNAME}/.bashrc" | xargs dos2unix && \
    dos2unix -ic "/docker/start.sh" | xargs dos2unix && \
    dos2unix -ic "/docker/login.sh" | xargs dos2unix && \
    dos2unix -ic "/usr/local/bin/startup" | xargs dos2unix && \
    chmod +x "/usr/local/bin/startup"

# user account configuration
RUN mkdir -p /home/${USERNAME}/.ssh && \
    mkdir -p /home/${USERNAME}/.vscode-server && \
    mkdir -p /home/${USERNAME}/projects
RUN chown -R ${UID}:${GID} /home/${USERNAME}

USER ${USERNAME}

RUN git clone https://github.com/google/CFU-Playground.git /home/${USERNAME}/CFU-Playground && \
    cd /home/${USERNAME}/CFU-Playground && \
    git reset --hard 094d4e8 && \
    { echo "y"; echo "Y"; } | ./scripts/setup && \
    mv proj/proj.mk /tmp/ && \
    rm -rf /home/${USERNAME}/CFU-Playground/.git && \
    rm -rf /home/${USERNAME}/CFU-Playground/proj && \
    mkdir /home/${USERNAME}/CFU-Playground/proj

WORKDIR /home/${USERNAME}/CFU-Playground/proj

CMD [ "/bin/bash", "-c", "bash -x /docker/start.sh > /docker/start.log 2>&1" ]
