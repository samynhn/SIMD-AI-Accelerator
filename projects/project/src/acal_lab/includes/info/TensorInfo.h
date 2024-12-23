#ifndef SRC_ACAL_LAB_INCLUDES_INFO_TENSORINFO_H_
#define SRC_ACAL_LAB_INCLUDES_INFO_TENSORINFO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

namespace acal_lab {

typedef struct TensorInfo {
	int     N;
	int     C;
	int     H;
	int     W;
	int8_t* data;
} tensorInfo;

}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_INFO_TENSORINFO_H_
