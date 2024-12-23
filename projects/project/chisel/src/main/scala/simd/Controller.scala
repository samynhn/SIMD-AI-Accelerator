package simd

import chisel3._
import chisel3.util._

class Controller extends Module {
  val io = IO(new Bundle {
    val cmd_payload = Flipped(Decoupled(new CfuInPayload()))
    val rsp_payload = Decoupled(new CfuOutPayload())

    val rsMatch     = Input(Bool())
    val addSubOpSel = Output(AddSubActivationOp())
    val mulOpSel    = Output(MulOp())
    val qntOpSel    = Output(QntOp())
    val wenRs       = Output(Bool())
    val wenRd       = Output(Bool())
    val outputSel   = Output(OutputSel())
  })

  val funct = io.cmd_payload.bits.funct7 ## io.cmd_payload.bits.funct3

  when(io.cmd_payload.valid & io.rsp_payload.ready) {
    // AddSubActivationUnit controll
    io.addSubOpSel := MuxLookup(
      funct,
      AddSubActivationOp.NONE,
      Seq(
        "b0000000_000".U -> AddSubActivationOp.ADDI8I8S_VV,
        "b0000000_001".U -> AddSubActivationOp.ADDI16I16S_VV,
        "b0000001_000".U -> AddSubActivationOp.SUBI8I8S_VV,
        "b0000001_001".U -> AddSubActivationOp.SUBI16I16S_VV,
        "b1000000_000".U -> AddSubActivationOp.ADDI8I8S_VX,
        "b1000000_001".U -> AddSubActivationOp.ADDI16I16S_VX,
        "b1000001_000".U -> AddSubActivationOp.SUBI8I8S_VX,
        "b1000001_001".U -> AddSubActivationOp.SUBI16I16S_VX,
        "b0001111_000".U -> AddSubActivationOp.SCMPLE8,
      )
    )

    // AddSubActivationUnit MulUnit controll
    io.mulOpSel := MuxLookup(
      funct,
      MulOp.NONE,
      Seq(
        "b0000010_000".U -> MulOp.AMULI8I8S_VV,
        "b0000010_100".U -> MulOp.PMULI8I16S_VV_L,
        "b0000010_101".U -> Mux(
          io.rsMatch,
          MulOp.NONE,
          MulOp.PMULI8I16S_VV_H
        ),
        "b1000010_000".U -> MulOp.AMULI8I8S_VX,
        "b1000010_100".U -> MulOp.PMULI8I16S_VX_L,
        "b1000010_101".U -> Mux(
          io.rsMatch,
          MulOp.NONE,
          MulOp.PMULI8I16S_VX_H
        )
      )
    )

    //QuantUnit controll
    io.qntOpSel := MuxLookup(
      funct,
      QntOp.NONE,
      Seq(
        "b0000111_000".U -> QntOp.QNT_INFO,
        "b0000111_001".U -> QntOp.QNTI16I8S_VV_NQ,
        "b0000111_010".U -> QntOp.QNTI16I8S_VV_AQ,
        "b0000010_001".U -> QntOp.AMULI8I8S_VV_AQ,
        "b1000010_001".U -> QntOp.AMULI8I8S_VX_AQ
      )
    )

    // Register controll
    io.wenRs := MuxLookup(
      funct,
      false.B,
      Seq(
        "b0000010_100".U -> true.B,
        "b1000010_100".U -> true.B
      )
    )
    io.wenRd := MuxLookup(
      funct,
      false.B,
      Seq(
        "b0000010_100".U -> true.B,
        "b1000010_100".U -> true.B
      )
    )
  }.otherwise {
    io.addSubOpSel := AddSubActivationOp.NONE
    io.mulOpSel    := MulOp.NONE
    io.qntOpSel    := QntOp.NONE
    io.wenRs       := false.B
    io.wenRd       := false.B
  }

  // Output controll
  io.cmd_payload.ready   := true.B
  io.rsp_payload.valid   := io.cmd_payload.valid & io.rsp_payload.ready
  io.rsp_payload.bits.rd := DontCare

  when(io.addSubOpSel =/= AddSubActivationOp.NONE) {
    io.outputSel := OutputSel.ADDSUB
  }.elsewhen(io.mulOpSel =/= MulOp.NONE) {
    io.outputSel := OutputSel.MUL
  }.elsewhen(io.qntOpSel =/= QntOp.NONE) {
    io.outputSel := OutputSel.QNT
  }.otherwise {
    io.outputSel := OutputSel.REG
  }
}
