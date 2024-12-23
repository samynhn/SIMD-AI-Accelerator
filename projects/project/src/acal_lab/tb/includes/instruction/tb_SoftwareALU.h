#ifndef SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SOFTWAREALU_H_
#define SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SOFTWAREALU_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "tb_SimdUtil.h"

namespace acal_lab {
namespace tb {

void i8i8_alu_vv(operation op, int8_t rd[4], int8_t rs1[4], int8_t rs2[4], int sc, int zpt);
void i8i8_alu_vx(operation op, int8_t rd[4], int8_t rs1[4], int32_t rs2, int sc, int zpt);
void i16i16_alu_vv(operation op, int16_t rd[2], int16_t rs1[2], int16_t rs2[2], int sc, int zpt);
void i16i16_alu_vx(operation op, int16_t rd[2], int16_t rs1[2], int32_t rs2, int sc, int zpt);
void i8i16_alu_vv(operation op, int16_t rd[4], int8_t rs1[4], int8_t rs2[4], int sc, int zpt);
void i8i16_alu_vx(operation op, int16_t rd[2], int8_t rs1[4], int32_t rs2, int sc, int zpt);

}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SOFTWAREALU_H_
