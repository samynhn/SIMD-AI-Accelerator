#include "acal_lab/tb/includes/models/AlexNet/tb_AlexNet.h"

// Quantization Information
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Conv1.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Conv2.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Conv3.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Conv4.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Conv5.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Gemm1.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Gemm2.h"
#include "acal_lab/tb/includes/models/AlexNet/quantInfo/tb_qInfo_Gemm3.h"

// input Testbench
#include "acal_lab/tb/includes/models/AlexNet/data/tb_data_1.h"
#include "acal_lab/tb/includes/models/AlexNet/data/tb_data_2.h"

// Model Weight
#include "acal_lab/tb/includes/models/AlexNet/weights/conv_0_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/conv_10_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/conv_3_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/conv_6_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/conv_8_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/gemm_0_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/gemm_2_weight.h"
#include "acal_lab/tb/includes/models/AlexNet/weights/gemm_4_weight.h"

namespace acal_lab {
namespace tb {

bool tb_AlexNet(testbench pic) {
	int8_t* data0 = (pic == testbench::PICTURE_0) ? (int8_t*)tb_data_1 : (int8_t*)tb_data_2;

	int8_t  conv1[CONV_1_OPT_C * CONV_1_OPT_H * CONV_1_OPT_W] = {0};
	int8_t  relu1[RELU_1_OPT_C * RELU_1_OPT_H * RELU_1_OPT_W] = {0};
	int8_t  mxpl1[MXPL_1_OPT_C * MXPL_1_OPT_H * MXPL_1_OPT_W] = {0};
	int8_t  conv2[CONV_2_OPT_C * CONV_2_OPT_H * CONV_2_OPT_W] = {0};
	int8_t  relu2[RELU_2_OPT_C * RELU_2_OPT_H * RELU_2_OPT_W] = {0};
	int8_t  mxpl2[MXPL_2_OPT_C * MXPL_2_OPT_H * MXPL_2_OPT_W] = {0};
	int8_t  conv3[CONV_3_OPT_C * CONV_3_OPT_H * CONV_3_OPT_W] = {0};
	int8_t  relu3[RELU_3_OPT_C * RELU_3_OPT_H * RELU_3_OPT_W] = {0};
	int8_t  conv4[CONV_4_OPT_C * CONV_4_OPT_H * CONV_4_OPT_W] = {0};
	int8_t  relu4[RELU_4_OPT_C * RELU_4_OPT_H * RELU_4_OPT_W] = {0};
	int8_t  conv5[CONV_5_OPT_C * CONV_5_OPT_H * CONV_5_OPT_W] = {0};
	int8_t  relu5[RELU_5_OPT_C * RELU_5_OPT_H * RELU_5_OPT_W] = {0};
	int8_t  mxpl3[MXPL_3_OPT_C * MXPL_3_OPT_H * MXPL_3_OPT_W] = {0};
	int8_t  gemm1[GEMM_1_OPT_H * GEMM_1_OPT_W]                = {0};
	int8_t  relu6[RELU_6_OPT_C * RELU_6_OPT_H * RELU_6_OPT_W] = {0};
	int8_t  gemm2[GEMM_2_OPT_H * GEMM_2_OPT_W]                = {0};
	int8_t  relu7[RELU_7_OPT_C * RELU_7_OPT_H * RELU_7_OPT_W] = {0};
	int8_t  data1[GEMM_3_OPT_H * GEMM_3_OPT_W]                = {0};
	int8_t* conv1_w                                           = (int8_t*)conv_0_weight;
	int8_t  conv1_b[CONV_1_B_W]                               = {0};
	int8_t* conv2_w                                           = (int8_t*)conv_3_weight;
	int8_t  conv2_b[CONV_2_B_W]                               = {0};
	int8_t* conv3_w                                           = (int8_t*)conv_6_weight;
	int8_t  conv3_b[CONV_3_B_W]                               = {0};
	int8_t* conv4_w                                           = (int8_t*)conv_8_weight;
	int8_t  conv4_b[CONV_4_B_W]                               = {0};
	int8_t* conv5_w                                           = (int8_t*)conv_10_weight;
	int8_t  conv5_b[CONV_5_B_W]                               = {0};
	int8_t* gemm1_w                                           = (int8_t*)gemm_0_weight;
	int8_t  gemm1_b[GEMM_1_B_H * GEMM_1_B_W]                  = {0};
	int8_t* gemm2_w                                           = (int8_t*)gemm_2_weight;
	int8_t  gemm2_b[GEMM_2_B_H * GEMM_2_B_W]                  = {0};
	int8_t* gemm3_w                                           = (int8_t*)gemm_4_weight;
	int8_t  gemm3_b[GEMM_3_B_H * GEMM_3_B_W]                  = {0};

	// Quantization Information
	quantiInfo conv1_q = {.scaling_factor = (int8_t)tb_qInfo_Conv1[0], .zero_point = (int8_t)tb_qInfo_Conv1[1]};
	quantiInfo conv2_q = {.scaling_factor = (int8_t)tb_qInfo_Conv2[0], .zero_point = (int8_t)tb_qInfo_Conv2[1]};
	quantiInfo conv3_q = {.scaling_factor = (int8_t)tb_qInfo_Conv3[0], .zero_point = (int8_t)tb_qInfo_Conv3[1]};
	quantiInfo conv4_q = {.scaling_factor = (int8_t)tb_qInfo_Conv4[0], .zero_point = (int8_t)tb_qInfo_Conv4[1]};
	quantiInfo conv5_q = {.scaling_factor = (int8_t)tb_qInfo_Conv5[0], .zero_point = (int8_t)tb_qInfo_Conv5[1]};
	quantiInfo gemm1_q = {.scaling_factor = (int8_t)tb_qInfo_Gemm1[0], .zero_point = (int8_t)tb_qInfo_Gemm1[1]};
	quantiInfo gemm2_q = {.scaling_factor = (int8_t)tb_qInfo_Gemm2[0], .zero_point = (int8_t)tb_qInfo_Gemm2[1]};
	quantiInfo gemm3_q = {.scaling_factor = (int8_t)tb_qInfo_Gemm3[0], .zero_point = (int8_t)tb_qInfo_Gemm3[1]};

	tensorInfo data0_0 = {.N = 1, .C = DATA_0_C, .H = DATA_0_H, .W = DATA_0_W, .data = data0};  // -------- / Conv_1 I
	tensorInfo conv1_1 = {
	    .N = 1, .C = CONV_1_OPT_C, .H = CONV_1_OPT_H, .W = CONV_1_OPT_W, .data = conv1};  // Conv_1 O / ReLU_1 I
	tensorInfo relu1_2 = {
	    .N = 1, .C = RELU_1_OPT_C, .H = RELU_1_OPT_H, .W = RELU_1_OPT_W, .data = relu1};  // ReLU_1 O / MxPl_1 I
	tensorInfo mxpl1_3 = {
	    .N = 1, .C = MXPL_1_OPT_C, .H = MXPL_1_OPT_H, .W = MXPL_1_OPT_W, .data = mxpl1};  // MxPl_1 O / Conv_2 I
	tensorInfo conv2_4 = {
	    .N = 1, .C = CONV_2_OPT_C, .H = CONV_2_OPT_H, .W = CONV_2_OPT_W, .data = conv2};  // Conv_2 O / ReLU_2 I
	tensorInfo relu2_5 = {
	    .N = 1, .C = RELU_2_OPT_C, .H = RELU_2_OPT_H, .W = RELU_2_OPT_W, .data = relu2};  // ReLU_2 O / MxPl_2 I
	tensorInfo mxpl2_6 = {
	    .N = 1, .C = MXPL_2_OPT_C, .H = MXPL_2_OPT_H, .W = MXPL_2_OPT_W, .data = mxpl2};  // MxPl_2 O / Conv_3 I
	tensorInfo conv3_7 = {
	    .N = 1, .C = CONV_3_OPT_C, .H = CONV_3_OPT_H, .W = CONV_3_OPT_W, .data = conv3};  // Conv_3 O / ReLU_3 I
	tensorInfo relu3_8 = {
	    .N = 1, .C = RELU_3_OPT_C, .H = RELU_3_OPT_H, .W = RELU_3_OPT_W, .data = relu3};  // ReLU_3 O / Conv_3 I
	tensorInfo conv4_9 = {
	    .N = 1, .C = CONV_4_OPT_C, .H = CONV_4_OPT_H, .W = CONV_4_OPT_W, .data = conv4};  // Conv_4 O / ReLU_4 I
	tensorInfo relu4_10 = {
	    .N = 1, .C = RELU_4_OPT_C, .H = RELU_4_OPT_H, .W = RELU_4_OPT_W, .data = relu4};  // ReLU_4 O / Conv_5 I
	tensorInfo conv5_11 = {
	    .N = 1, .C = CONV_5_OPT_C, .H = CONV_5_OPT_H, .W = CONV_5_OPT_W, .data = conv5};  // Conv_5 O / ReLU_5 I
	tensorInfo relu5_12 = {
	    .N = 1, .C = RELU_5_OPT_C, .H = RELU_5_OPT_H, .W = RELU_5_OPT_W, .data = relu5};  // ReLU_5 O / MxPl_3 I
	tensorInfo mxpl3_13 = {
	    .N = 1, .C = MXPL_3_OPT_C, .H = MXPL_3_OPT_H, .W = MXPL_3_OPT_W, .data = mxpl3};  // MxPl_3 O / Fltn_0 I
	tensorInfo fltn1_14 = {
	    .N = 1, .C = FLTN_0_OPT_C, .H = FLTN_0_OPT_H, .W = FLTN_0_OPT_W, .data = gemm1};          // Fltn_0 O / Gemm_1 I
	tensorInfo gemm1_15 = {.N = 1, .C = 1, .H = GEMM_1_OPT_H, .W = GEMM_1_OPT_W, .data = gemm1};  // Gemm_1 O / ReLU_6 I
	tensorInfo relu6_16 = {
	    .N = 1, .C = RELU_6_OPT_C, .H = RELU_6_OPT_H, .W = RELU_6_OPT_W, .data = relu6};          // ReLU_6 O / Gemm_2 I
	tensorInfo gemm2_17 = {.N = 1, .C = 1, .H = GEMM_2_OPT_H, .W = GEMM_2_OPT_W, .data = gemm2};  // Gemm_2 O / ReLU_7 I
	tensorInfo relu7_18 = {.N = 1, .C = 1, .H = RELU_7_OPT_H, .W = RELU_7_OPT_W, .data = relu7};  // ReLU_7 O / Gemm_3 I
	tensorInfo data1_19 = {.N = 1, .C = 1, .H = GEMM_3_OPT_H, .W = GEMM_3_OPT_W, .data = data1};  // Gemm_3 O / --------

	// Weight And Bias
	tensorInfo conv1_w_0 = {
	    .N = CONV_1_W_N, .C = CONV_1_W_C, .H = CONV_1_W_H, .W = CONV_1_W_W, .data = conv1_w};  // Conv_1
	tensorInfo conv1_b_0 = {.N = 1, .C = 1, .H = 1, .W = CONV_1_B_W, .data = conv1_b};         // Conv_1
	tensorInfo conv2_w_4 = {
	    .N = CONV_2_W_N, .C = CONV_2_W_C, .H = CONV_2_W_H, .W = CONV_2_W_W, .data = conv2_w};  // Conv_2
	tensorInfo conv2_b_4 = {.N = 1, .C = 1, .H = 1, .W = CONV_2_B_W, .data = conv2_b};         // Conv_2
	tensorInfo conv3_w_7 = {
	    .N = CONV_3_W_N, .C = CONV_3_W_C, .H = CONV_3_W_H, .W = CONV_3_W_W, .data = conv3_w};  // Conv_3
	tensorInfo conv3_b_7 = {.N = 1, .C = 1, .H = 1, .W = CONV_3_B_W, .data = conv3_b};         // Conv_3
	tensorInfo conv4_w_9 = {
	    .N = CONV_4_W_N, .C = CONV_4_W_C, .H = CONV_4_W_H, .W = CONV_4_W_W, .data = conv4_w};     // Conv_4
	tensorInfo conv4_b_9  = {.N = 1, .C = 1, .H = 1, .W = CONV_4_B_W, .data = conv4_b};           // Conv_4
	tensorInfo conv5_w_11 = {.N = 1, .C = 1, .H = CONV_5_W_H, .W = CONV_5_W_W, .data = conv5_w};  // Conv_5
	tensorInfo conv5_b_11 = {.N = 1, .C = 1, .H = 1, .W = CONV_5_B_W, .data = conv5_b};           // Conv_5
	tensorInfo gemm1_w_14 = {.N = 1, .C = 1, .H = GEMM_1_W_H, .W = GEMM_1_W_W, .data = gemm1_w};  // Gemm_1
	tensorInfo gemm1_b_14 = {.N = 1, .C = 1, .H = GEMM_2_B_H, .W = GEMM_2_B_W, .data = gemm1_b};  // Gemm_1
	tensorInfo gemm2_w_16 = {.N = 1, .C = 1, .H = GEMM_2_W_H, .W = GEMM_2_W_W, .data = gemm2_w};  // Gemm_2
	tensorInfo gemm2_b_16 = {.N = 1, .C = 1, .H = GEMM_2_B_H, .W = GEMM_2_B_W, .data = gemm2_b};  // Gemm_2
	tensorInfo gemm3_w_18 = {.N = 1, .C = 1, .H = GEMM_3_W_H, .W = GEMM_3_W_W, .data = gemm3_w};  // Gemm_3
	tensorInfo gemm3_b_18 = {.N = 1, .C = 1, .H = GEMM_3_B_H, .W = GEMM_3_B_W, .data = gemm3_b};  // Gemm_3
	// operator Information
	gemmInfo   gemm1_info   = {.weight = gemm1_w_14, .bias = gemm1_b_14};
	gemmInfo   gemm2_info   = {.weight = gemm2_w_16, .bias = gemm2_b_16};
	gemmInfo   gemm3_info   = {.weight = gemm3_w_18, .bias = gemm3_b_18};
	convInfo   conv1_info   = {.kernelSize = CONV_1_KERNEL_SIZE,
	                           .stride     = CONV_1_STRIDE,
	                           .padding    = CONV_1_PADDING,
	                           .kernel     = conv1_w_0,
	                           .bias       = conv1_b_0};
	convInfo   conv2_info   = {.kernelSize = CONV_2_KERNEL_SIZE,
	                           .stride     = CONV_2_STRIDE,
	                           .padding    = CONV_2_PADDING,
	                           .kernel     = conv2_w_4,
	                           .bias       = conv2_b_4};
	convInfo   conv3_info   = {.kernelSize = CONV_3_KERNEL_SIZE,
	                           .stride     = CONV_3_STRIDE,
	                           .padding    = CONV_3_PADDING,
	                           .kernel     = conv3_w_7,
	                           .bias       = conv3_b_7};
	convInfo   conv4_info   = {.kernelSize = CONV_4_KERNEL_SIZE,
	                           .stride     = CONV_4_STRIDE,
	                           .padding    = CONV_4_PADDING,
	                           .kernel     = conv4_w_9,
	                           .bias       = conv4_b_9};
	convInfo   conv5_info   = {.kernelSize = CONV_5_KERNEL_SIZE,
	                           .stride     = CONV_5_STRIDE,
	                           .padding    = CONV_5_PADDING,
	                           .kernel     = conv5_w_11,
	                           .bias       = conv5_b_11};
	mxPlInfo   mxpl1_info   = {.kernelSize = MXPL_1_KERNEL_SIZE, .stride = MXPL_1_STRIDE, .padding = MXPL_1_PADDING};
	mxPlInfo   mxpl2_info   = {.kernelSize = MXPL_2_KERNEL_SIZE, .stride = MXPL_2_STRIDE, .padding = MXPL_2_PADDING};
	mxPlInfo   mxpl3_info   = {.kernelSize = MXPL_3_KERNEL_SIZE, .stride = MXPL_3_STRIDE, .padding = MXPL_3_PADDING};
	convInfo   convInfo[5]  = {conv1_info, conv2_info, conv3_info, conv4_info, conv5_info};
	gemmInfo   gemmInfo[3]  = {gemm1_info, gemm2_info, gemm3_info};
	mxPlInfo   mxplInfo[3]  = {mxpl1_info, mxpl2_info, mxpl3_info};
	tensorInfo tnsrInfo[20] = {data0_0,  conv1_1,  relu1_2,  mxpl1_3,  conv2_4,  relu2_5,  mxpl2_6,
	                           conv3_7,  relu3_8,  conv4_9,  relu4_10, conv5_11, relu5_12, mxpl3_13,
	                           fltn1_14, gemm1_15, relu6_16, gemm2_17, relu7_18, data1_19};
	quantiInfo quanInfo[8]  = {conv1_q, conv2_q, conv3_q, conv4_q, conv5_q, gemm1_q, gemm2_q, gemm3_q};
	acal_lab::alexNet(convInfo, gemmInfo, mxplInfo, tnsrInfo, quanInfo);

	return tb_check(data1_19, pic);
}

bool tb_check(tensorInfo output, testbench pic) {
	int8_t ans = (pic == testbench::PICTURE_0) ? (int8_t)3 : (int8_t)5;

	int8_t _max   = 0;
	int8_t maxIdx = 0;
	for (int i = 0; i < output.W; ++i)
		if (_max <= output.data[i]) _max = output.data[i], maxIdx = i;
	printf("MaxIdx: %d\n", maxIdx);
	printf("ans: %d\n", ans);
	return maxIdx == ans;
}

}  // namespace tb
}  // namespace acal_lab
