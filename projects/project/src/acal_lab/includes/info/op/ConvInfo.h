#ifndef SRC_ACAL_LAB_INCLUDES_INFO_OP_CONVINFO_H_
#define SRC_ACAL_LAB_INCLUDES_INFO_OP_CONVINFO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info/TensorInfo.h"

namespace acal_lab {

typedef struct ConvInfo {
	int        kernelSize;
	int        stride;
	int        padding;
	tensorInfo kernel;
	tensorInfo bias;
} convInfo;

}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_INFO_OP_CONVINFO_H_
