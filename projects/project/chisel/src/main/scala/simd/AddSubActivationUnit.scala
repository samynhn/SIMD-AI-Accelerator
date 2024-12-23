package simd

import chisel3._
import chisel3.util._
import chisel3.experimental.ChiselEnum

object AddSubActivationOp extends ChiselEnum {
  val NONE                       = Value
  val ADDI8I8S_VV, ADDI16I16S_VV = Value
  val SUBI8I8S_VV, SUBI16I16S_VV = Value
  val ADDI8I8S_VX, ADDI16I16S_VX = Value
  val SUBI8I8S_VX, SUBI16I16S_VX = Value
  val SCMPLE8 = Value
}

class AddSubActivationUnit extends Module {
  val io = IO(new Bundle {
    val opSel = Input(AddSubActivationOp())
    val rs1   = Input(UInt(32.W))
    val rs2   = Input(UInt(32.W))
    val rd    = Output(UInt(32.W))
  })

  val rs1ByteArray = Wire(Vec(4, UInt(8.W)))
  val rs2ByteArray = Wire(Vec(4, UInt(8.W)))
  val rdByteArray  = Wire(Vec(4, UInt(8.W)))
  val rdByteConcat = Wire(UInt(32.W))
  val rs1HalfArray = Wire(Vec(2, UInt(16.W)))
  val rs2HalfArray = Wire(Vec(2, UInt(16.W)))
  val rdHalfArray  = Wire(Vec(2, UInt(16.W)))
  val rdHalfConcat = Wire(UInt(32.W))

  // 8-bit wire assignment
  for (i <- 0 until 4) {
    rs1ByteArray(i) := io.rs1(8 * i + 7, 8 * i)
    rs2ByteArray(i) := io.rs2(8 * i + 7, 8 * i)

    rdByteArray(i) := MuxLookup(
      io.opSel.asUInt,
      DontCare,
      Seq(
        AddSubActivationOp.ADDI8I8S_VV.asUInt -> (rs1ByteArray(i).asSInt + rs2ByteArray(i).asSInt).asUInt,
        AddSubActivationOp.SUBI8I8S_VV.asUInt -> (rs1ByteArray(i).asSInt - rs2ByteArray(i).asSInt).asUInt,
        AddSubActivationOp.ADDI8I8S_VX.asUInt -> (rs1ByteArray(i).asSInt + rs2ByteArray(0).asSInt).asUInt,
        AddSubActivationOp.SUBI8I8S_VX.asUInt -> (rs1ByteArray(i).asSInt - rs2ByteArray(0).asSInt).asUInt,
        AddSubActivationOp.SCMPLE8.asUInt -> Mux(
          rs1ByteArray(i).asSInt <= rs2ByteArray(i).asSInt,
          rs2ByteArray(i),
          rs1ByteArray(i)
        )
      )
    )
  }

  // 16-bit wire assignment
  for (i <- 0 until 2) {
    rs1HalfArray(i) := io.rs1(16 * i + 15, 16 * i)
    rs2HalfArray(i) := io.rs2(16 * i + 15, 16 * i)

    rdHalfArray(i) := MuxLookup(
      io.opSel.asUInt,
      DontCare,
      Seq(
        AddSubActivationOp.ADDI16I16S_VV.asUInt -> (rs1HalfArray(i).asSInt + rs2HalfArray(i).asSInt).asUInt,
        AddSubActivationOp.SUBI16I16S_VV.asUInt -> (rs1HalfArray(i).asSInt - rs2HalfArray(i).asSInt).asUInt,
        AddSubActivationOp.ADDI16I16S_VX.asUInt -> (rs1HalfArray(i).asSInt + rs2HalfArray(0).asSInt).asUInt,
        AddSubActivationOp.SUBI16I16S_VX.asUInt -> (rs1HalfArray(i).asSInt - rs2HalfArray(0).asSInt).asUInt
      )
    )
  }

  rdByteConcat := Seq.range(3, -1, -1).map { i => rdByteArray(i) }.reduce(_ ## _)
  rdHalfConcat := Seq.range(1, -1, -1).map { i => rdHalfArray(i) }.reduce(_ ## _)

  when(io.opSel.isOneOf(
    AddSubActivationOp.ADDI8I8S_VV,
    AddSubActivationOp.SUBI8I8S_VV,
    AddSubActivationOp.ADDI8I8S_VX,
    AddSubActivationOp.SUBI8I8S_VX,
    AddSubActivationOp.SCMPLE8
  )) {
    io.rd := rdByteConcat
  }.elsewhen(io.opSel.isOneOf(
    AddSubActivationOp.ADDI16I16S_VV,
    AddSubActivationOp.SUBI16I16S_VV,
    AddSubActivationOp.ADDI16I16S_VX,
    AddSubActivationOp.SUBI16I16S_VX
  )) {
    io.rd := rdHalfConcat
  }.otherwise {
    io.rd := DontCare
  }
}
