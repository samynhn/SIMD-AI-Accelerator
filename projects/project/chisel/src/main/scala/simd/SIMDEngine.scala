package simd

import chisel3._
import chisel3.util._
import chisel3.experimental.ChiselEnum

object OutputSel extends ChiselEnum {
  val ADDSUB, MUL, QNT, REG = Value
}

class CfuInPayload extends Bundle {
  val funct7 = UInt(7.W)
  val funct3 = UInt(3.W)
  val rs1    = SInt(32.W)
  val rs2    = SInt(32.W)
}

class CfuOutPayload extends Bundle {
  val rd = SInt(32.W)
}

class SIMDEngine extends Module {
  val io = IO(new Bundle {
    val cmd_payload = Flipped(Decoupled(new CfuInPayload()))
    val rsp_payload = Decoupled(new CfuOutPayload())
  })

  val controller           = Module(new Controller())
  val addSubActivationUnit = Module(new AddSubActivationUnit())
  val mulUnit              = Module(new MulUnit())
  val qntUnit              = Module(new QntUnit())
  val register             = Module(new Register())

  controller.io.cmd_payload <> io.cmd_payload
  controller.io.rsp_payload <> io.rsp_payload

  controller.io.rsMatch         := register.io.rsMatch
  addSubActivationUnit.io.opSel := controller.io.addSubOpSel
  addSubActivationUnit.io.rs1   := io.cmd_payload.bits.rs1.asUInt
  addSubActivationUnit.io.rs2   := io.cmd_payload.bits.rs2.asUInt
  mulUnit.io.opSel              := controller.io.mulOpSel
  mulUnit.io.rs1                := io.cmd_payload.bits.rs1.asUInt
  mulUnit.io.rs2                := io.cmd_payload.bits.rs2.asUInt
  qntUnit.io.opSel              := controller.io.qntOpSel
  qntUnit.io.rs1                := io.cmd_payload.bits.rs1.asUInt
  qntUnit.io.rs2                := io.cmd_payload.bits.rs2.asUInt
  register.io.rs1               := io.cmd_payload.bits.rs1.asUInt
  register.io.rs2               := io.cmd_payload.bits.rs2.asUInt
  register.io.rdMsbIn           := mulUnit.io.rdMsb
  register.io.wenRs             := controller.io.wenRs
  register.io.wenRd             := controller.io.wenRd

  io.rsp_payload.bits.rd := MuxLookup(
    controller.io.outputSel.asUInt,
    DontCare,
    Seq(
      OutputSel.ADDSUB.asUInt -> addSubActivationUnit.io.rd.asSInt,
      OutputSel.MUL.asUInt    -> mulUnit.io.rd.asSInt,
      OutputSel.QNT.asUInt    -> qntUnit.io.rd.asSInt,
      OutputSel.REG.asUInt    -> register.io.rdMsbOut.asSInt
    )
  )
}

import chisel3.stage.ChiselStage
object SIMDEngineApp extends App {
  (new ChiselStage).emitVerilog(
    new SIMDEngine(),
    Array(
      "-td",
      "build",                       // Work directory (default: '.')
      "-X",
      "verilog",                     // The FIRRTL compiler to use (default: verilog)
      // "--no-dce",                    // Disable dead code elimination
      "--emit-circuit",
      "verilog",                     // Run the specified module emitter (one file per module)
      "--emission-options",
      "disableMemRandomization",     // Options to disable random initialization for memory and registers
      "--emission-options",
      "disableRegisterRandomization" // Options to disable random initialization for memory and registers
    )
  )
}
