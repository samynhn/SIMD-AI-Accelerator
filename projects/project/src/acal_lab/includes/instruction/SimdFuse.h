#ifndef SRC_ACAL_LAB_INCLUDES_INSTRUCTION_SIMDFUSE_H_
#define SRC_ACAL_LAB_INCLUDES_INSTRUCTION_SIMDFUSE_H_
#include <stdint.h>
#include <stdlib.h>

#include "SimdInst.h"

namespace acal_lab {

/**
 * @brief 13-3-1-3 : Signed Integer Precise(Lossless) Multiplication : sPMULI8I16S_vv
 * @note `inline void sADDI8I8S_vv(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param c `int16_t[4]` Output array to store the INT16 values.
 * @param a `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param b `int8_t[4]` Input array[0:3] containing INT8 values.
 */
void sPMULI8I16S_vv(int16_t c[4], int8_t a[4], int8_t b[4]);

/**
 * @brief 13-3-1-3 : Signed Integer Precise(Lossless) Multiplication : sPMULI8I16S_vx
 * @note `inline void sPMULI8I16S_vx(int8_t c[4], int8_t a[4], int8_t b)`
 * @param c `int16_t[4]` Output array to store the INT16 values.
 * @param a `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param b `int8_t` Input containing INT8 values.
 */
void sPMULI8I16S_vx(int16_t c[4], int8_t a[4], int8_t b);

}  // namespace acal_lab

#endif  // SRC_ACAL_LAB_INCLUDES_INSTRUCTION_SIMDFUSE_H_
