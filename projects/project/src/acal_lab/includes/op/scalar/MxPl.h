#ifndef SRC_ACAL_LAB_INCLUDES_OP_SCALAR_MXPL_H_
#define SRC_ACAL_LAB_INCLUDES_OP_SCALAR_MXPL_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info/op/MxPlInfo.h"
#include "acal_lab/includes/op/Op.h"

namespace acal_lab {
namespace scalar {

class MxPl : public Operator {
public:
	MxPl(tensorInfo* opt, tensorInfo* ipt, mxPlInfo* opInfo, QauntiType qType)
	    : Operator(opt, ipt, qType), info(opInfo) {
		execFunction = reinterpret_cast<void (Operator::*)()>(&MxPl::exec);
	}

	void exec() override;

protected:
	mxPlInfo* info;
};

}  //  namespace scalar
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_OP_SCALAR_MXPL_H_
