#ifndef SRC_ACAL_LAB_INCLUDES_OP_OP_H_
#define SRC_ACAL_LAB_INCLUDES_OP_OP_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info.h"
#include "acal_lab/includes/instruction.h"
#include "perf.h"

namespace acal_lab {

class Operator {
public:
	Operator(tensorInfo* opt, tensorInfo* ipt, qauntiType qType) : output(opt), input(ipt) {
		switch (qType) {
			case PER_LAYER_NAIVE_QUANTI: execFunction = &Operator::execPerLayerNaiveQuant; break;
			case PER_LAYER_ADVANCE_QUANTI: execFunction = &Operator::execPerLayerAdvanceQuant; break;
			case PER_OPERATION_NAIVE_QUANTI: execFunction = &Operator::execPerOperationNaiveQuant; break;
			case PER_OPERATION_ADVANCE_QUANTI: execFunction = &Operator::execPerOperationAdvanceQuant; break;
			default: execFunction = &Operator::exec; break;
		}
	}
	virtual inline unsigned preOp() {
		unsigned start = perf_get_mcycle();
		printf("Entering loop at: %u\n", start);
		return start;
	}
	virtual inline unsigned postOp() {
		unsigned end = perf_get_mcycle();
		printf("Exiting loop at: %u\n", end);
		return end;
	}
	void                execute() {
        // unsigned start = preOp();
        (this->*execFunction)();
        // unsigned end = postOp();
		// printf("Total cycles: %u\n", end - start);
	}
	virtual void execPerLayerNaiveQuant() {}
	virtual void execPerLayerAdvanceQuant() {}
	virtual void execPerOperationNaiveQuant() {}
	virtual void execPerOperationAdvanceQuant() {}
	virtual void exec(){};

protected:
	tensorInfo* output;
	tensorInfo* input;
	void (Operator::*execFunction)();
};

}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_OP_OP_H_