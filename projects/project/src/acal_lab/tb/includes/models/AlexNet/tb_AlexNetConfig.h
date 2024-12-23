#ifndef SRC_ACAL_LAB_TB_INCLUDES_MODELS_ALEXNET_TB_ALEXNETCONFIG_H_
#define SRC_ACAL_LAB_TB_INCLUDES_MODELS_ALEXNET_TB_ALEXNETCONFIG_H_

// Input Size
#define DATA_0_C 4
#define DATA_0_H 64
#define DATA_0_W 64

// Layer 1 : Convolution
#define CONV_1_W_N         16
#define CONV_1_W_C         4
#define CONV_1_W_H         9
#define CONV_1_W_W         9
#define CONV_1_B_W         16
#define CONV_1_KERNEL_SIZE 9
#define CONV_1_STRIDE      1
#define CONV_1_PADDING     0
#define CONV_1_OPT_C       16
#define CONV_1_OPT_H       56
#define CONV_1_OPT_W       56
// Layer 2 : ReLU
#define RELU_1_OPT_C 16
#define RELU_1_OPT_H 56
#define RELU_1_OPT_W 56
// Layer 3 : MaxPool
#define MXPL_1_KERNEL_SIZE 2
#define MXPL_1_STRIDE      2
#define MXPL_1_PADDING     0
#define MXPL_1_OPT_C       16
#define MXPL_1_OPT_H       28
#define MXPL_1_OPT_W       28
// Layer 4 : Convolution
#define CONV_2_W_N         32
#define CONV_2_W_C         16
#define CONV_2_W_H         5
#define CONV_2_W_W         5
#define CONV_2_B_W         32
#define CONV_2_KERNEL_SIZE 5
#define CONV_2_STRIDE      1
#define CONV_2_PADDING     0
#define CONV_2_OPT_C       32
#define CONV_2_OPT_H       24
#define CONV_2_OPT_W       24
// Layer 5 : ReLU
#define RELU_2_OPT_C 32
#define RELU_2_OPT_H 24
#define RELU_2_OPT_W 24
// Layer 6 : MaxPool
#define MXPL_2_KERNEL_SIZE 2
#define MXPL_2_STRIDE      2
#define MXPL_2_PADDING     0
#define MXPL_2_OPT_C       32
#define MXPL_2_OPT_H       12
#define MXPL_2_OPT_W       12
// Layer 7 : Convolution
#define CONV_3_W_N         64
#define CONV_3_W_C         32
#define CONV_3_W_H         3
#define CONV_3_W_W         3
#define CONV_3_B_W         64
#define CONV_3_KERNEL_SIZE 3
#define CONV_3_STRIDE      1
#define CONV_3_PADDING     0
#define CONV_3_OPT_C       64
#define CONV_3_OPT_H       10
#define CONV_3_OPT_W       10
// Layer 8 : ReLU
#define RELU_3_OPT_C 64
#define RELU_3_OPT_H 10
#define RELU_3_OPT_W 10
// Layer 9 : Convolution
#define CONV_4_W_N         32
#define CONV_4_W_C         64
#define CONV_4_W_H         3
#define CONV_4_W_W         3
#define CONV_4_B_W         32
#define CONV_4_KERNEL_SIZE 3
#define CONV_4_STRIDE      1
#define CONV_4_PADDING     0
#define CONV_4_OPT_C       32
#define CONV_4_OPT_H       8
#define CONV_4_OPT_W       8
// Layer 10 : ReLU
#define RELU_4_OPT_C 32
#define RELU_4_OPT_H 8
#define RELU_4_OPT_W 8
// Layer 11 : Convolution
#define CONV_5_W_N         32
#define CONV_5_W_C         32
#define CONV_5_W_H         3
#define CONV_5_W_W         3
#define CONV_5_B_W         32
#define CONV_5_KERNEL_SIZE 3
#define CONV_5_STRIDE      1
#define CONV_5_PADDING     0
#define CONV_5_OPT_C       32
#define CONV_5_OPT_H       6
#define CONV_5_OPT_W       6
// Layer 12 : ReLU
#define RELU_5_OPT_C 32
#define RELU_5_OPT_H 6
#define RELU_5_OPT_W 6
// Layer 13 : MaxPool
#define MXPL_3_OPT_C       32
#define MXPL_3_OPT_H       3
#define MXPL_3_OPT_W       3
#define MXPL_3_KERNEL_SIZE 2
#define MXPL_3_STRIDE      2
#define MXPL_3_PADDING     0
// Layer 14 : Flatten
#define FLTN_0_OPT_C 1
#define FLTN_0_OPT_H 1
#define FLTN_0_OPT_W 288
// Layer 15 : GEMM
#define GEMM_1_W_H   144
#define GEMM_1_W_W   288
#define GEMM_1_B_H   1
#define GEMM_1_B_W   144
#define GEMM_1_OPT_H 1
#define GEMM_1_OPT_W 144
// Layer 16 : ReLU
#define RELU_6_OPT_C 1
#define RELU_6_OPT_H 1
#define RELU_6_OPT_W 144
// Layer 17 : GEMM
#define GEMM_2_W_H   144
#define GEMM_2_W_W   144
#define GEMM_2_B_H   1
#define GEMM_2_B_W   144
#define GEMM_2_OPT_H 1
#define GEMM_2_OPT_W 144
// Layer 18 : ReLU
#define RELU_7_OPT_C 1
#define RELU_7_OPT_H 1
#define RELU_7_OPT_W 144
// Layer 19 : GEMM
#define GEMM_3_W_H   10
#define GEMM_3_W_W   144
#define GEMM_3_B_H   1
#define GEMM_3_B_W   10
#define GEMM_3_OPT_H 1
#define GEMM_3_OPT_W 10

#endif  // SRC_ACAL_LAB_TB_INCLUDES_MODELS_ALEXNET_TB_ALEXNETCONFIG_H_
