package simd.hw

import util.Random
import chisel3._
import chiseltest._
import org.scalatest.freespec.AnyFreeSpec
import chisel3.experimental.BundleLiterals._
import chiseltest.{WriteVcdAnnotation, VerilatorBackendAnnotation}

class TestHw2Addition extends AnyFreeSpec with ChiselScalatestTester {
  "SIMD Execution Unit should execute sADDI8I8S.vv instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000000", 2)
      val funct3 = Integer.parseInt("000", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => (rs1_arr(i) + rs2_arr(i)).toByte)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sADDI16I16S.vv instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000000", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rs2_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rd_arr  = (0 to 1).map(i => (rs1_arr(i) + rs2_arr(i)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(Seq.range(1, -1, -1).map { i =>
          (rs1_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.bits.rs2.poke(Seq.range(1, -1, -1).map { i =>
          (rs2_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sADDI8I8S.vx instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000000", 2)
      val funct3 = Integer.parseInt("000", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => (rs1_arr(i) + rs2_arr(0)).toByte)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sADDI16I16S.vx instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000000", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rs2_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rd_arr  = (0 to 1).map(i => (rs1_arr(i) + rs2_arr(0)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(Seq.range(1, -1, -1).map { i =>
          (rs1_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.bits.rs2.poke(Seq.range(1, -1, -1).map { i =>
          (rs2_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }
}

class TestHw2Substraction extends AnyFreeSpec with ChiselScalatestTester {
  "SIMD Execution Unit should execute sSUBI8I8S.vv instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000001", 2)
      val funct3 = Integer.parseInt("000", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => (rs1_arr(i) - rs2_arr(i)).toByte)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sSUBI16I16S.vv instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000001", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rs2_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rd_arr  = (0 to 1).map(i => (rs1_arr(i) - rs2_arr(i)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(Seq.range(1, -1, -1).map { i =>
          (rs1_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.bits.rs2.poke(Seq.range(1, -1, -1).map { i =>
          (rs2_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sSUBI8I8S.vx instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000001", 2)
      val funct3 = Integer.parseInt("000", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => (rs1_arr(i) - rs2_arr(0)).toByte)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sSUBI16I16S.vx instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000001", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rs2_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rd_arr  = (0 to 1).map(i => (rs1_arr(i) - rs2_arr(0)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(Seq.range(1, -1, -1).map { i =>
          (rs1_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.bits.rs2.poke(Seq.range(1, -1, -1).map { i =>
          (rs2_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }
}

class TestHw2Multiplication extends AnyFreeSpec with ChiselScalatestTester {
  "SIMD Execution Unit should execute sAMULI8I8S.vv.NQ instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000010", 2)
      val funct3 = Integer.parseInt("000", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => (rs1_arr(i) * rs2_arr(i)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => ((rd_arr(i).toInt & 0xff00) >> 8) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sAMULI8I8S.vx.NQ instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000010", 2)
      val funct3 = Integer.parseInt("000", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => (rs1_arr(i) * rs2_arr(0)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => ((rd_arr(i).toInt & 0xff00) >> 8) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sPMULI8I16S.vv.L instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000010", 2)
      val funct3 = Integer.parseInt("100", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 1).map(i => (rs1_arr(i) * rs2_arr(i)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sPMULI8I16S.vv.H instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000010", 2)
      val funct3 = Integer.parseInt("101", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (2 to 3).map(i => (rs1_arr(i) * rs2_arr(i)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sPMULI8I16S.vx.L instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000010", 2)
      val funct3 = Integer.parseInt("100", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 1).map(i => (rs1_arr(i) * rs2_arr(0)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sPMULI8I16S.vx.H instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("1000010", 2)
      val funct3 = Integer.parseInt("101", 2)

      for (i <- 0 until 50) {
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (2 to 3).map(i => (rs1_arr(i) * rs2_arr(0)).toShort)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(Seq.range(1, -1, -1).map { i =>
          (rd_arr(i).toInt & 0xffff) << (16 * i)
        }.reduce(_ | _))
        dut.clock.step(1)
      }
    }
  }
}

class TestHw2Quantization extends AnyFreeSpec with ChiselScalatestTester {
  def quantize(value: Short, scaling: Int, zero: Int): Byte = {
    var result: Int = 0
    if (scaling >= 0) {
      result = (value.toInt >> scaling) + zero
    } else {
      result = (value.toInt << (scaling * (-1))) + zero
    }
    return result.toByte
  }

  "SIMD Execution Unit should execute sAMULI8I8S.vv.AQ instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val qnt_info_funct7 = Integer.parseInt("0000111", 2)
      val qnt_info_funct3 = Integer.parseInt("000", 2)

      val funct7 = Integer.parseInt("0000010", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        // setup quantization
        val scaling_factor: Int = Random.nextInt(15) - 7
        val zero: Int           = Random.nextInt(15) - 7

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(qnt_info_funct7)
        dut.io.cmd_payload.bits.funct3.poke(qnt_info_funct3)
        dut.io.cmd_payload.bits.rs1.poke(scaling_factor)
        dut.io.cmd_payload.bits.rs2.poke(zero)
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.clock.step(1)

        // calculation
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => quantize((rs1_arr(i) * rs2_arr(i)).toShort, scaling_factor, zero))

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sAMULI8I8S.vx.AQ instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val qnt_info_funct7 = Integer.parseInt("0000111", 2)
      val qnt_info_funct3 = Integer.parseInt("000", 2)

      val funct7 = Integer.parseInt("1000010", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        // setup quantization
        val scaling_factor: Int = Random.nextInt(15) - 7
        val zero: Int           = Random.nextInt(15) - 7

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(qnt_info_funct7)
        dut.io.cmd_payload.bits.funct3.poke(qnt_info_funct3)
        dut.io.cmd_payload.bits.rs1.poke(scaling_factor)
        dut.io.cmd_payload.bits.rs2.poke(zero)
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.clock.step(1)

        // calculation
        val rs1_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rs2_arr = (0 to 3).map(_ => Random.nextInt().toByte)
        val rd_arr  = (0 to 3).map(i => quantize((rs1_arr(i) * rs2_arr(0)).toShort, scaling_factor, zero))

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(3, -1, -1).map { i => (rs1_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(3, -1, -1).map { i => (rs2_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sQNTI16I8S.vv.NQ instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val funct7 = Integer.parseInt("0000111", 2)
      val funct3 = Integer.parseInt("001", 2)

      for (i <- 0 until 50) {
        // calculation
        val rs1_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rs2_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rd_arr  = (0 to 3).map(i => (rs1_arr ++ rs2_arr)(i) >> 8)

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(1, -1, -1).map { i => (rs1_arr(i).toInt & 0xffff) << (16 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(1, -1, -1).map { i => (rs2_arr(i).toInt & 0xffff) << (16 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }

  "SIMD Execution Unit should execute sQNTI16I8S.vv.AQ instructions" in {
    test(new simd.SIMDEngine()).withAnnotations(Seq(
      WriteVcdAnnotation,
      VerilatorBackendAnnotation
    )) { dut =>
      val qnt_info_funct7 = Integer.parseInt("0000111", 2)
      val qnt_info_funct3 = Integer.parseInt("000", 2)

      val funct7 = Integer.parseInt("0000111", 2)
      val funct3 = Integer.parseInt("010", 2)

      for (i <- 0 until 50) {
        // setup quantization
        val scaling_factor: Int = Random.nextInt(15) - 7
        val zero: Int           = Random.nextInt(15) - 7

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(qnt_info_funct7)
        dut.io.cmd_payload.bits.funct3.poke(qnt_info_funct3)
        dut.io.cmd_payload.bits.rs1.poke(scaling_factor)
        dut.io.cmd_payload.bits.rs2.poke(zero)
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.clock.step(1)

        // calculation
        val rs1_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rs2_arr = (0 to 1).map(_ => Random.nextInt().toShort)
        val rd_arr  = (0 to 3).map(i => quantize((rs1_arr ++ rs2_arr)(i), scaling_factor, zero))

        dut.io.cmd_payload.valid.poke(true.B)
        dut.io.cmd_payload.bits.funct7.poke(funct7)
        dut.io.cmd_payload.bits.funct3.poke(funct3)
        dut.io.cmd_payload.bits.rs1.poke(
          Seq.range(1, -1, -1).map { i => (rs1_arr(i).toInt & 0xffff) << (16 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.bits.rs2.poke(
          Seq.range(1, -1, -1).map { i => (rs2_arr(i).toInt & 0xffff) << (16 * i) }.reduce(_ | _)
        )
        dut.io.cmd_payload.ready.expect(true.B)
        dut.io.rsp_payload.ready.poke(true.B)
        dut.io.rsp_payload.valid.expect(true.B)
        dut.io.rsp_payload.bits.rd.expect(
          Seq.range(3, -1, -1).map { i => (rd_arr(i).toInt & 0xff) << (8 * i) }.reduce(_ | _)
        )
        dut.clock.step(1)
      }
    }
  }
}
