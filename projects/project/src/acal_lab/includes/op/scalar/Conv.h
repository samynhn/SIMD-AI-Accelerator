#ifndef SRC_ACAL_LAB_INCLUDES_OP_SCALAR_CONV_H_
#define SRC_ACAL_LAB_INCLUDES_OP_SCALAR_CONV_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info/op/ConvInfo.h"
#include "acal_lab/includes/op/Op.h"

namespace acal_lab {
namespace scalar {

class Conv : public Operator {
public:
	Conv(tensorInfo* opt, tensorInfo* ipt, convInfo* opInfo, quantiInfo* quantInfo, QauntiType qType)
	    : Operator(opt, ipt, qType), info(opInfo), qInfo(quantInfo) {}

	void execPerLayerNaiveQuant() override;
	void execPerLayerAdvanceQuant() override;
	void execPerOperationNaiveQuant() override;
	void execPerOperationAdvanceQuant() override;

protected:
	convInfo*   info;
	quantiInfo* qInfo;
};

}  // namespace scalar
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_OP_SCALAR_CONV_H_
