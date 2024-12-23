#ifndef SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_RELU_H_
#define SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_RELU_H_

#include "acal_lab/includes/op/scalar/ReLU.h"
#include "acal_lab/includes/op/simd/ReLU.h"
#include "tb_Op.h"

namespace acal_lab {
namespace tb {

#define RELU_dimC 8
#define RELU_dimH 8
#define RELU_dimW 8

bool tb_ReLU();

}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_OP_SIMD_TB_RELU_H_
