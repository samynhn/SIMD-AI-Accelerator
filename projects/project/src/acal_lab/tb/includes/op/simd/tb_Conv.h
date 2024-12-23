#ifndef SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_CONV_H_
#define SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_CONV_H_

#include "acal_lab/includes/op/scalar/Conv.h"
#include "acal_lab/includes/op/simd/Conv.h"
#include "tb_Op.h"

namespace acal_lab {
namespace tb {

bool tb_Conv(testType);
bool tb_ConvPerOperationrNaiveQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, convInfo* opInfo,
                                    quantiInfo* quantInfo);
bool tb_ConvPerOperationAdvanceQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, convInfo* opInfo,
                                     quantiInfo* quantInfo);
bool tb_ConvPerLayerNaiveQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, convInfo* opInfo,
                               quantiInfo* quantInfo);
bool tb_ConvPerLayerAdvanceQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, convInfo* opInfo,
                                 quantiInfo* quantInfo);
}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_CONV_H_
