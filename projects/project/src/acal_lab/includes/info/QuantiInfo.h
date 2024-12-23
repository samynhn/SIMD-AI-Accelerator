#ifndef SRC_ACAL_LAB_INCLUDES_INFO_QUANTIINFO_H_
#define SRC_ACAL_LAB_INCLUDES_INFO_QUANTIINFO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

namespace acal_lab {

typedef enum QauntiType {
	PER_LAYER_NAIVE_QUANTI,
	PER_LAYER_ADVANCE_QUANTI,
	PER_OPERATION_NAIVE_QUANTI,
	PER_OPERATION_ADVANCE_QUANTI,
	GENERAL
} qauntiType;

typedef struct QuantiInfo {
	int8_t scaling_factor;
	int8_t zero_point;
} quantiInfo;

}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_INFO_QUANTIINFO_H_
