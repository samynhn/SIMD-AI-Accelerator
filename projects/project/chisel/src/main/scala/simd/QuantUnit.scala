package simd

import chisel3._
import chisel3.util._
import chisel3.experimental.ChiselEnum

object QntOp extends ChiselEnum {
    val NONE = Value
    val AMULI8I8S_VV_AQ, AMULI8I8S_VX_AQ = Value
    val QNT_INFO, QNTI16I8S_VV_NQ, QNTI16I8S_VV_AQ = Value
}

class QntUnit extends Module {
    val io = IO(new Bundle {
        val opSel = Input(QntOp())
        val rs1   = Input(UInt(32.W))
        val rs2   = Input(UInt(32.W))
        val rd    = Output(UInt(32.W))
    })

    val rs1ByteArray    = Wire(Vec(4, UInt(8.W)))
    val rs2ByteArray    = Wire(Vec(4, UInt(8.W)))
    val rdByteArray     = Wire(Vec(4, UInt(8.W)))
    val rdByteConcat    = Wire(UInt(32.W))
    val rs1HalfArray    = Wire(Vec(2, UInt(16.W)))
    val rs2HalfArray    = Wire(Vec(2, UInt(16.W)))
    

    val scaling_factor = RegInit(0.U(32.W))
    val zero_point = RegInit(0.U(32.W))

    for (i <- 0 until 4) {
        rs1ByteArray(i) := io.rs1(8 * i + 7, 8 * i)
        rs2ByteArray(i) := io.rs2(8 * i + 7, 8 * i)
    }
    
    for (i <- 0 until 2) {
        rs1HalfArray(i) := io.rs1(16 * i + 15, 16 * i)
        rs2HalfArray(i) := io.rs2(16 * i + 15, 16 * i)
    }

    when(io.opSel === QntOp.QNT_INFO) {
        scaling_factor := io.rs1
        zero_point := io.rs2
        for (i <- 0 until 4) {
            rdByteArray(i) := DontCare
        }
    }.elsewhen(io.opSel === QntOp.QNTI16I8S_VV_NQ) {
        rdByteArray(0) := (rs1HalfArray(0).asSInt >> 8.U).asUInt
        rdByteArray(1) := (rs1HalfArray(1).asSInt >> 8.U).asUInt
        rdByteArray(2) := (rs2HalfArray(0).asSInt >> 8.U).asUInt
        rdByteArray(3) := (rs2HalfArray(1).asSInt >> 8.U).asUInt  
    }.elsewhen(io.opSel === QntOp.QNTI16I8S_VV_AQ) {
        when(scaling_factor.asSInt < 0.S) {
            rdByteArray(0) := ((rs1HalfArray(0).asSInt << (-scaling_factor)(3,0)) + zero_point.asSInt).asUInt
            rdByteArray(1) := ((rs1HalfArray(1).asSInt << (-scaling_factor)(3,0)) + zero_point.asSInt).asUInt
            rdByteArray(2) := ((rs2HalfArray(0).asSInt << (-scaling_factor)(3,0)) + zero_point.asSInt).asUInt
            rdByteArray(3) := ((rs2HalfArray(1).asSInt << (-scaling_factor)(3,0)) + zero_point.asSInt).asUInt
        }.otherwise {
            rdByteArray(0) := ((rs1HalfArray(0).asSInt >> scaling_factor(3,0)) + zero_point.asSInt).asUInt
            rdByteArray(1) := ((rs1HalfArray(1).asSInt >> scaling_factor(3,0)) + zero_point.asSInt).asUInt
            rdByteArray(2) := ((rs2HalfArray(0).asSInt >> scaling_factor(3,0)) + zero_point.asSInt).asUInt
            rdByteArray(3) := ((rs2HalfArray(1).asSInt >> scaling_factor(3,0)) + zero_point.asSInt).asUInt
        }
    }.elsewhen(io.opSel === QntOp.AMULI8I8S_VV_AQ) {
        when(scaling_factor.asSInt < 0.S) {
            for (i <- 0 until 4) {
                rdByteArray(i) := (((rs1ByteArray(i).asSInt * rs2ByteArray(i).asSInt) << (-scaling_factor)(3,0)) + zero_point.asSInt).asUInt
            }
        }.otherwise {
            for (i <- 0 until 4) {
                rdByteArray(i) := (((rs1ByteArray(i).asSInt * rs2ByteArray(i).asSInt) >> scaling_factor(3,0)) + zero_point.asSInt).asUInt
            }
        }
    }.elsewhen(io.opSel === QntOp.AMULI8I8S_VX_AQ) {
        when(scaling_factor.asSInt < 0.S) {
            for (i <- 0 until 4) {
                rdByteArray(i) := (((rs1ByteArray(i).asSInt * rs2ByteArray(0).asSInt) << (-scaling_factor)(3,0)) + zero_point.asSInt).asUInt
            }
        }.otherwise {
            for (i <- 0 until 4) {
                rdByteArray(i) := (((rs1ByteArray(i).asSInt * rs2ByteArray(0).asSInt) >> scaling_factor(3,0)) + zero_point.asSInt).asUInt
            }
        }
    }.otherwise {
        for (i <- 0 until 4) {
            rdByteArray(i) := DontCare
        }
    }

    rdByteConcat := Seq.range(3, -1, -1).map { i => rdByteArray(i) }.reduce(_ ## _)
    io.rd := MuxLookup(
        io.opSel.asUInt,
        DontCare,
        Seq(
            QntOp.AMULI8I8S_VV_AQ.asUInt -> rdByteConcat,
            QntOp.AMULI8I8S_VX_AQ.asUInt -> rdByteConcat,
            QntOp.QNTI16I8S_VV_NQ.asUInt -> rdByteConcat,
            QntOp.QNTI16I8S_VV_AQ.asUInt -> rdByteConcat
        )
    )
}