package simd

import chisel3._
import chisel3.util._

class Register extends Module {
  val io = IO(new Bundle {
    val rs1      = Input(UInt(32.W))
    val rs2      = Input(UInt(32.W))
    val rdMsbIn  = Input(UInt(32.W))
    val wenRs    = Input(Bool())
    val wenRd    = Input(Bool())
    val rsMatch  = Output(Bool())
    val rdMsbOut = Output(UInt(32.W))
  })

  val rsReg    = RegInit(VecInit(Seq.fill(2)(0.U(32.W))))
  val rdMsbReg = RegInit(0.U(32.W))

  // register update
  rsReg(0) := Mux(io.wenRs, io.rs1, rsReg(0))
  rsReg(1) := Mux(io.wenRs, io.rs2, rsReg(1))
  rdMsbReg := Mux(io.wenRd, io.rdMsbIn, rdMsbReg)

  // output signals
  io.rdMsbOut := rdMsbReg
  io.rsMatch  := (io.rs1 === rsReg(0)) & (io.rs2 === rsReg(1))
}
