#   SIMD Instruction Set Support for AI Computing

## Usage

1.  Build docker workspace for CFU playground
    ```sh
    ./run start
    ```
1. Navigate to the project directory:
    ```sh
    cd projects/project
    ```
2. Build the project:
    ```sh
    make renode-headless
    ```
3. Press `space`.
4. Press `3`.
5. Press `h` to test the whole AlexNet.
6. Press `esc` and `Ctrl-D` to exit.

## Note

- The code for AlexNet is located at:
    ```
    /projects/project/src/acal_lab/libs/models/AlexNet/AlexNet.cc
    ```
    
  Modify the type of the function of the model component (e.g., conv/gemm) to use SIMD or scalar. This allows you to observe the speed difference between SIMD and serial execution.


- The SIMD implementation of the model components can be found at:
    ```
    /projects/project/src/acal_lab/libs/op/simd
    ```
  This directory contains the SIMD instructions we created.

- The hardware design of the SIMD instructions is implemented in:
    ```
    /projects/project/chisel/src/main/scala/simd
    ```