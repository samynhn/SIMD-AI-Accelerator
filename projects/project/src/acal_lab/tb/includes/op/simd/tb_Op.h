#ifndef SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_OP_H_
#define SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_OP_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "acal_lab/includes/info.h"

#define _8_BIT_  256
#define _16_BIT_ 65536

namespace acal_lab {
namespace tb {

typedef enum TestType { LAB, HW } testType;

bool compare8(tensorInfo*, tensorInfo*);
void randomInit8(tensorInfo*);

}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_OP_H_