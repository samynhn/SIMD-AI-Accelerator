#ifndef SRC_ACAL_LAB_INCLUDES_OP_SIMD_GEMM_H_
#define SRC_ACAL_LAB_INCLUDES_OP_SIMD_GEMM_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info/op/GemmInfo.h"
#include "acal_lab/includes/op/Op.h"

namespace acal_lab {
namespace simd {

class Gemm : public Operator {
public:
	Gemm(tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo, quantiInfo* quantInfo, QauntiType qType)
	    : Operator(opt, ipt, qType), info(opInfo), qInfo(quantInfo) {}

	void execPerLayerNaiveQuant() override;
	void execPerLayerAdvanceQuant() override;
	void execPerOperationNaiveQuant() override;
	void execPerOperationAdvanceQuant() override;

protected:
	gemmInfo*   info;
	quantiInfo* qInfo;
};

}  // namespace simd
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_OP_SIMD_GEMM_H_
