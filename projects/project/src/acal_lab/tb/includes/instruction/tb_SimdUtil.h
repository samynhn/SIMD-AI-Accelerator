#ifndef SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SIMDUTIL_H_
#define SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SIMDUTIL_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TB_DATA_SIZE_16_BIT 256

namespace acal_lab {
namespace tb {
typedef enum Operation { ADD, SUB, PMUL, AMULNQ, AMULAQ } operation;

void randinit_i8i8_vv(int8_t rs1[4], int8_t rs2[4], int8_t rdhw[4], int8_t rdtb[4]);
void randinit_i8i8_vx(int8_t rs1[4], int8_t* rs2, int8_t rdhw[4], int8_t rdtb[4]);
void randinit_i16i16_vv(int16_t rs1[2], int16_t rs2[2], int16_t rdhw[2], int16_t rdtb[2]);
void randinit_i16i16_vx(int16_t rs1[2], int16_t* rs2, int16_t rdhw[2], int16_t rdtb[2]);
void randinit_i8i16_vv(int8_t rs1[4], int8_t rs2[4], int16_t rdhw[4], int16_t rdtb[4]);
void randinit_i8i16_vx(int8_t rs1[4], int8_t* rs2, int16_t rdhw[4], int16_t rdtb[4]);
int  i8_check(int8_t rdhw[4], int8_t rdtb[4]);
int  i16_check(int16_t rdhw[2], int16_t rdtb[2]);

}  // namespace tb
}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_TB_INCLUDES_INSTRUCTION_TB_SIMDUTIL_H_
