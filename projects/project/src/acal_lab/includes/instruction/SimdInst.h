#ifndef SRC_ACAL_LAB_INCLUDES_INSTRUCTION_SIMDINST_H_
#define SRC_ACAL_LAB_INCLUDES_INSTRUCTION_SIMDINST_H_
#pragma GCC optimize("-fno-strict-aliasing")

#include <stdint.h>
#include <stdlib.h>

// CFU Framework
#include "cfu.h"

// 13-3-1   : Integer Extension
/*****************************************************************************
 *                       13-3-1-1 Signed Integer Addition                    *
 *****************************************************************************/
/**
 * @brief 13-3-1-1.1 : Signed Integer Addition : sADDI8I8S_vv
 * @note `inline void sADDI8I8S_vv(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param arrI8c(rd) `int8_t[4]` Output array to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param arrI8b(rs2) `int8_t[4]` Input array[0:3] containing INT8 values.
 */
#define sADDI8I8S_vv(arrI8c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b0000000, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

/**
 * @brief 13-3-1-1.2 : Signed Integer Addition : sADDI16I16S_vv
 * @note `inline void sADDI16I16S_vv(int16_t c[2], int16_t a[2], int16_t b[2])`
 * @param arrI16c(rd) `int16_t[2]` Output array to store the INT16 values.
 * @param arrI16a(rs1) `int16_t[2]` Input array[0:1] containing INT16 values.
 * @param arrI16b(rs2) `int16_t[2]` Input array[0:1] containing INT16 values.
 */
#define sADDI16I16S_vv(arrI16c, arrI16a, arrI16b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b001, 0b0000000, *(int32_t*)(arrI16a), *(int32_t*)(arrI16b)))

/**
 * @brief 13-3-1-1.3 : Signed Integer Addition : sADDI8I8S_vx
 * @note `inline void sADDI8I8S_vx(int8_t c[4], int8_t a[4], int8_t b)`
 * @param arrI8c(rd) `int8_t[4]` Output array[0:3] to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param I8b(rs2) `int8_t` Input containing INT8 values.
 */
#define sADDI8I8S_vx(arrI8c, arrI8a, I8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b1000000, *(int32_t*)(arrI8a), (int32_t)(I8b)))

/**
 * @brief 13-3-1-1.4 : Signed Integer Addition : sADDI16I16S_vx
 * @note `inline void sADDI16I16S_vx(int16_t c[2], int16_t a[2], int16_t b)`
 * @param arrI16c(rd)  `int16_t[2]` Output array to store the INT16 values.
 * @param arrI16a(rs1) `int16_t[2]` Input array[0:1] containing INT16 values.
 * @param I16b(rs2) `int16_t` Input containing INT16 values.
 */
#define sADDI16I16S_vx(arrI16c, arrI16a, I16b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b001, 0b1000000, *(int32_t*)(arrI16a), (int32_t)(I16b)))

/******************************************************************************
 *                     13-3-1-2 : Signed Integer Substration                   *
 ******************************************************************************/
/**
 * @brief 13-3-1-2.1 : Signed Integer Substration : sSUBI8I8S_vv
 * @note `inline void sSUBI8I8S_vv(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param arrI8c(rd) `int8_t[4]` Output array to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param arrI8b(rs2) `int8_t[4]` Input array[0:3] containing INT8 values.
 */
#define sSUBI8I8S_vv(arrI8c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b0000001, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

/**
 * @brief 13-3-1-2.2 : Signed Integer Substration : sSUBI16I16S_vv
 * @note `inline void sSUBI16I16S_vv(int16_t c[2], int16_t a[2], int16_t b[2])`
 * @param arrI16c(rd) `int16_t[2]` Output array to store the INT16 values.
 * @param arrI16a(rs1) `int16_t[2]` Input array[0:1] containing INT16 values.
 * @param arrI16b(rs2) `int16_t[2]` Input array[0:1] containing INT16 values.
 */
#define sSUBI16I16S_vv(arrI16c, arrI16a, arrI16b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b001, 0b0000001, *(int32_t*)(arrI16a), *(int32_t*)(arrI16b)))

/**
 * @brief 13-3-1-2.3 : Signed Integer Substration : sSUBI8I8S_vx
 * @note `inline void sSUBI8I8S_vx(int8_t c[4], int8_t a[4], int8_t b)`
 * @param arrI8c(rd) `int8_t[4]` Output array[0:3] to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param I8b(rs2) `int8_t` Input containing INT8 values.
 */
#define sSUBI8I8S_vx(arrI8c, arrI8a, I8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b1000001, *(int32_t*)(arrI8a), (int32_t)(I8b)))
/**
 * @brief 13-3-1-2.4 : Signed Integer Substration : sSUBI16I16S_vx
 * @note `inline void sSUBI16I16S_vx(int16_t c[2], int16_t a[2], int16_t b)`
 * @param arrI16c(rd)  `int16_t[2]` Output array to store the INT16 values.
 * @param arrI16a(rs1) `int16_t[2]` Input array[0:1] containing INT16 values.
 * @param I16b(rs2) `int16_t` Input containing INT16 values.
 */
#define sSUBI16I16S_vx(arrI16c, arrI16a, I16b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b001, 0b1000001, *(int32_t*)(arrI16a), (int32_t)(I16b)))

/******************************************************************************
 *        13-3-1-3 : Signed Integer Precise(Lossless) Multiplication           *
 ******************************************************************************/
/**
 * @brief 13-3-1-3.1 : Signed Integer Precise(Lossless) Multiplication
 * @note `inline void sPMULI8I16S_vv_L(int16_t c[2], int8_t a[4], int8_t b[4])`
 * @param arrI16c(rd) `int16_t[2]` Output array to store the INT16 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param arrI8b(rs2) `int8_t[4]` Input array[0:3] containing INT8 values.
 */
#define sPMULI8I16S_vv_L(arrI16c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b100, 0b0000010, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

/**
 * @brief 13-3-1-3.2 : Signed Integer Precise(Lossless) Multiplication
 * @note `inline void sPMULI8I16S_vv_H(int16_t c[2], int8_t a[4], int8_t b[4])`
 * @param arrI16c(rd) `int16_t[2]` Output array to store the INT16 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param arrI8b(rs2) `int8_t[4]` Input array[0:3] containing INT8 values.
 */
#define sPMULI8I16S_vv_H(arrI16c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b101, 0b0000010, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

/**
 * @brief 13-3-1-3.3 : Signed Integer Precise(Lossless) Multiplication
 * @note `inline void sPMULI8I16S_vx_L(int16_t c[2], int8_t a[4], int8_t b)`
 * @param arrI16c(rd) `int16_t[2]` Output array to store the INT16 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param I8b(rs2) `int8_t` Input containing INT8 values.
 */
#define sPMULI8I16S_vx_L(arrI16c, arrI8a, I8b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b100, 0b1000010, *(int32_t*)(arrI8a), (int32_t)(I8b)))

/**
 * @brief 13-3-1-3.4 : Signed Integer Precise(Lossless) Multiplication
 * @note `inline void sPMULI8I16S_vx_H(int16_t c[2], int8_t a[4], int8_t b)`
 * @param arrI16c(rd) `int16_t[2]` Output array to store the INT16 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param I8b(rs2) `int8_t` Input containing INT8 values.
 */
#define sPMULI8I16S_vx_H(arrI16c, arrI8a, I8b) \
	(*(int32_t*)(arrI16c) = cfu_op(0b101, 0b1000010, *(int32_t*)(arrI8a), (int32_t)(I8b)))

/******************************************************************************
 *         13-3-1-4 : Signed Integer Approximate(Lossy) Multiplication         *
 ******************************************************************************/
/**
 * @brief 13-3-1-4.1 : Signed Integer Approximate(Lossy) MUL w/ Naive Quantization
 * @note `inline void sAMULI8I8S_vv_NQ(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param arrI8c(rd) `int8_t[4]` Output array to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param arrI8b(rs2) `int8_t[4]` Input array[0:3] containing INT8 values.
 */
#define sAMULI8I8S_vv_NQ(arrI8c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b0000010, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

/**
 * @brief 13-3-1-4.2 : Signed Integer Approximate(Lossy) MUL w/ Advance Quantization
 * @note `inline void sAMULI8I8S_vv_AQ(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param arrI8c(rd) `int8_t[4]` Output array to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param arrI8b(rs2) `int8_t[4]` Input array[0:3] containing INT8 values.
 */
#define sAMULI8I8S_vv_AQ(arrI8c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b001, 0b0000010, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

/**
 * @brief 13-3-1-4.3 : Signed Integer Approximate(Lossy) MUL w/ Naive Quantization
 * @note `inline void sAMULI8I8S_vx_NQ(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param arrI8c(rd) `int8_t[4]` Output array[0:3] to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param I8b(rs2) `int8_t` Input containing INT8 values.
 */
#define sAMULI8I8S_vx_NQ(arrI8c, arrI8a, I8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b1000010, *(int32_t*)(arrI8a), (int32_t)(I8b)))

/**
 * @brief 13-3-1-4.4 : Signed Integer Approximate(Lossy) MUL w/ Advance Quantization
 * @note `inline void sAMULI8I8S_vx_AQ(int8_t c[4], int8_t a[4], int8_t b[4])`
 * @param arrI8c(rd) `int8_t[4]` Output array[0:3] to store the INT8 values.
 * @param arrI8a(rs1) `int8_t[4]` Input array[0:3] containing INT8 values.
 * @param I8b(rs2) `int8_t` Input containing INT8 values.
 */
#define sAMULI8I8S_vx_AQ(arrI8c, arrI8a, I8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b001, 0b1000010, *(int32_t*)(arrI8a), (int32_t)(I8b)))

/******************************************************************************
 *                           13-3-2 : Quantization                           *
 ******************************************************************************/
/**
 * @brief 13-3-2-1 : Setup Quantization Parameters (scaling factor and zero point) in CFU unit.
 * @note `inline void sAMULI8I8S_vx_AQ(int32_t scalingFactor, int32_t zeroPt)`
 * @param scalingFactor(rs1) Scaling factor(S)= 2^-rs1
 * @param zeroPt(rs2) zero point(Z) = rs2
 */
#define sQNT_INFO(scalingFactor, zeroPt) cfu_op(0b000, 0b0000111, scalingFactor, zeroPt)

/**
 * @brief 13-3-2-2 : (Naive Quantization) Quantize an INT16 vector to INT8 vector.
 * @note `inline void sQNTI16I8S_vv_NQ(int8_t c[4], int16_t a[2], int16_t b[2])`
 * @param arrI8c(rd) Output array to store the quantized INT8 values.
 * @param arrI16a(rs1) Input array[0:1] containing INT16 values to be quantized.
 * @param arrI16b(rs2) Input array[2:3] containing INT16 values to be quantized.
 */
#define sQNTI16I8S_vv_NQ(arrI8c, arrI16a, arrI16b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b001, 0b0000111, *(int32_t*)(arrI16a), *(int32_t*)(arrI16b)))

/**
 * @brief 13-3-2-3 : (Advance Quantization) Quantize an INT16 vector to INT8 vector with Quantization Parameters.
 * @note `inline void sQNTI16I8S_vv_AQ(int8_t c[4], int16_t a[2], int16_t b[2])`
 * @param arrI8c(rd) Output array to store the quantized INT8 values.
 * @param arrI16a(rs1) Input array[0:1] containing INT16 values to be quantized.
 * @param arrI16b(rs2) Input array[2:3] containing INT16 values to be quantized.
 */
#define sQNTI16I8S_vv_AQ(arrI8c, arrI16a, arrI16b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b010, 0b0000111, *(int32_t*)(arrI16a), *(int32_t*)(arrI16b)))


#define sSCMPLE8(arrI8c, arrI8a, arrI8b) \
	(*(int32_t*)(arrI8c) = cfu_op(0b000, 0b0001111, *(int32_t*)(arrI8a), *(int32_t*)(arrI8b)))

#endif  // SRC_ACAL_LAB_INCLUDES_INSTRUCTION_SIMDINST_H_
