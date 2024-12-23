#ifndef SRC_ACAL_LAB_INCLUDES_INFO_OP_GEMMINFO_H_
#define SRC_ACAL_LAB_INCLUDES_INFO_OP_GEMMINFO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info/TensorInfo.h"

namespace acal_lab {

typedef struct GemmInfo {
	tensorInfo weight;
	tensorInfo bias;
} gemmInfo;

}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_INFO_OP_GEMMINFO_H_
