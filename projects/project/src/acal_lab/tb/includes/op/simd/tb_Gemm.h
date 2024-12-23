#ifndef SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_GEMM_H_
#define SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_GEMM_H_

#include "acal_lab/includes/op/scalar/Gemm.h"
#include "acal_lab/includes/op/simd/Gemm.h"
#include "tb_Op.h"

#define GEMM_dimM 8
#define GEMM_dimN 8
#define GEMM_dimK 8

namespace acal_lab {
namespace tb {

bool tb_Gemm(testType);
bool tb_GemmPerOperationrNaiveQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                                    quantiInfo* quantInfo);
bool tb_GemmPerOperationAdvanceQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                                     quantiInfo* quantInfo);
bool tb_GemmPerLayerNaiveQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                               quantiInfo* quantInfo);
bool tb_GemmPerLayerAdvanceQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                                 quantiInfo* quantInfo);

}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_GEMM_H_
