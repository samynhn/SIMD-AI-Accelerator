#   SIMD Instruction Set Support for AI Computing
In this work, we conduct a detailed analysis of deep learning models to pinpoint modules with the highest computational overhead. To mitigate these bottlenecks, we design a custom SIMD (Single Instruction Multiple Data) instruction set, specifically designed to accelerate the computation of these performance-critical modules. By leveraging our tailored SIMD instructions, we achieve significant reductions in computational time, surpassing the performance of conventional serial implementations.

- For detailed technical information, please refer to [report.pdf](docs/report.pdf)
- For project presentation slides, see [slides.pdf](docs/slides.pdf)

## Usage

1.  Build docker workspace for CFU playground
    ```sh
    ./run start
    ```
2. Navigate to the project directory:
    ```sh
    cd proj/project
    ```
3.  Navigate to the chisel folder
    ```sh
    cd ./chisel
    ```
4.  Generate Verilog code according to Chisel design into `build/SIMDEngine.v`
    ```shell
    sbt 'runMain simd.SIMDEngineApp'
    ```
5.  Back to project directory
    ```sh
    cd ../
    ```

6. Build the project:
    ```sh
    make renode-headless
    ```
7. Press `space`.
8.  Press `3`.
9. Press `h` to test the whole AlexNet.
10. Press `esc` and `Ctrl-D` to exit.

## Note

- The code for AlexNet is located at:
    ```
    /proj/project/src/acal_lab/libs/models/AlexNet/AlexNet.cc
    ```
    
  Modify the type of the function of the model component (e.g., conv/gemm) to use SIMD or scalar. This allows you to observe the speed difference between SIMD and serial execution.


- The SIMD implementation of the model components can be found at:
    ```
    /proj/project/src/acal_lab/libs/op/simd
    ```
  This directory contains the SIMD instructions we created.

- The hardware design of the SIMD instructions is implemented in:
    ```
    /proj/project/chisel/src/main/scala/simd
    ```