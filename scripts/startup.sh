#!/bin/bash

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

cat <<EOF

    Welcome to use the Docker Workspace for CFU Playground.

    Develop all your projects in '~/CFU-Playground/proj' to keep them after the container closed.
    In addition, '~/.ssh' and '~/.vscode-server' is also mounted under 'temp/' of your host machine.

    The following are some useful commands for this environment.

    [ Container ]
        startup     : Show this message.
        ssh-keygen  : Generate SSH private & public key.
        exit        : Leave the container.

    [ Python virtual environment ]
        virtualenv venv             : Create a Python virtual environment in the current directory.
        source venv/bin/activate    : Activate a Python virtual environment.
        pip3 install -r <FILE>      : Install Python packages with a specified file. Only use it when venv is activated.
        pip3 list                   : Show installed Python packages in the current configuration.
        deactivate                  : Leave the current Python virtual environment.

    [ Python formatter ]
        yapf -i [-r] [-e PATTERN] [--style STYLE] FILES    : Format the Python codes.

EOF
