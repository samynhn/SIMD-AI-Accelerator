# SIMD Execution Unit in CFU Playground

## Usage
- Generate Verilog code according to Chisel design into `build/SIMDEngine.v`:
    ```shell
    sbt 'runMain simd.SIMDEngineApp'
    ```
- Execute all testbench:
    ```shell
    sbt test
    ```
- Execute specific testbench:
    ```shell
    sbt 'testOnly simd.<TESTBENCH_CLASS>'
    ```
    For example, use this command to run the `TestLab2Multiplication` class defined in `src/test/scala/simd/lab/lab8-2.scala`:
    ```shell
    sbt 'testOnly simd.lab.TestLab2Multiplication'
    ```
    Or, use this command to run all testbenches defined in `src/test/scala/simd/lab/lab8-2.scala`:
    ```shell
    sbt 'testOnly simd.lab.*'
    ```
