#ifndef SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SIMDINST_H_
#define SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SIMDINST_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// CFU Framework
#include "cfu.h"

// My Project
#include "acal_lab/includes/instruction.h"
#include "tb_SimdUtil.h"
#include "tb_SoftwareALU.h"

namespace acal_lab {
namespace tb {
// 8-2.1   : Integer Extension
// 8-2.1-1 : Signed Integer Addition
bool tb_sADDI8I8S_vv();
bool tb_sADDI16I16S_vv();
bool tb_sADDI8I8S_vx();
bool tb_sADDI16I16S_vx();
bool tb_sADDS_vv();
bool tb_sADDS_vx();
bool tb_sADDS();
// 8-2.1-2 : Signed Integer Substration
bool tb_sSUBI8I8S_vv();
bool tb_sSUBI16I16S_vv();
bool tb_sSUBI8I8S_vx();
bool tb_sSUBI16I16S_vx();
bool tb_sSUBS_vv();
bool tb_sSUBS_vx();
bool tb_sSUBS();
// 8-2.1-3 : Signed Integer Precise(Lossless) Multiplication
bool tb_sPMULI8I16S_vv_L();
bool tb_sPMULI8I16S_vv_H();
bool tb_sPMULI8I16S_vv_LH();
bool tb_sPMULI8I16S_vv_HL();
bool tb_sPMULI8I16S_vv();
bool tb_sPMULI8I16S_vx_L();
bool tb_sPMULI8I16S_vx_H();
bool tb_sPMULI8I16S_vx_LH();
bool tb_sPMULI8I16S_vx_HL();
bool tb_sPMULI8I16S_vx();
bool tb_sPMULI8I16S();
// 8-2.1-4 : Signed Integer Approximate(Lossy) Multiplication
bool tb_sAMULI8I8S_vv_NQ();
bool tb_sAMULI8I8S_vv_AQ();
bool tb_sAMULI8I8S_vv();
bool tb_sAMULI8I8S_vx_NQ();
bool tb_sAMULI8I8S_vx_AQ();
bool tb_sAMULI8I8S_vx();
bool tb_sAMULI8I8S();

}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SIMDINST_H_
