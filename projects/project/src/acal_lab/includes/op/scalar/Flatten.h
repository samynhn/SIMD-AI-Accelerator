#ifndef SRC_ACAL_LAB_INCLUDES_OP_SCALAR_FLATTEN_H_
#define SRC_ACAL_LAB_INCLUDES_OP_SCALAR_FLATTEN_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/op/Op.h"

namespace acal_lab {
namespace scalar {

class Flatten : public Operator {
public:
	Flatten(tensorInfo* opt, tensorInfo* ipt, QauntiType qType) : Operator(opt, ipt, qType) {
		execFunction = reinterpret_cast<void (Operator::*)()>(&Flatten::exec);
	}
	void exec() {}
};

}  // namespace scalar
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_OP_SCALAR_FLATTEN_H_
