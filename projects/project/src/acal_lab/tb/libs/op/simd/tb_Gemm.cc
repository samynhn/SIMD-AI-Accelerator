#include "acal_lab/tb/includes/op/simd/tb_Gemm.h"

#define TB_SIZE 100

namespace acal_lab {
namespace tb {

bool tb_GemmPerOperationrNaiveQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                                    quantiInfo* quantInfo) {
	int per_opeation_cnt = 0;
	int tb_idx           = TB_SIZE;
	while (tb_idx--) {
		randomInit8(ipt);
		randomInit8(&opInfo->bias);
		randomInit8(&opInfo->weight);
		simd::Gemm(opt, ipt, opInfo, quantInfo, PER_OPERATION_NAIVE_QUANTI).execute();
		scalar::Gemm(optTest, ipt, opInfo, quantInfo, PER_OPERATION_NAIVE_QUANTI).execute();
		per_opeation_cnt += compare8(optTest, opt);
	}
	printf("[ TEST ] `GEMM`  : per Operation  Naive  Quantization %3d/%3d\n", per_opeation_cnt, TB_SIZE);
	return per_opeation_cnt == TB_SIZE ? true : false;
}

bool tb_GemmPerLayerNaiveQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                               quantiInfo* quantInfo) {
	int per_layer_cnt = 0;
	int tb_idx        = TB_SIZE;
	while (tb_idx--) {
		randomInit8(ipt);
		randomInit8(&opInfo->bias);
		randomInit8(&opInfo->weight);
		simd::Gemm(opt, ipt, opInfo, quantInfo, PER_LAYER_NAIVE_QUANTI).execute();
		scalar::Gemm(optTest, ipt, opInfo, quantInfo, PER_LAYER_NAIVE_QUANTI).execute();
		per_layer_cnt += compare8(optTest, opt);
	}
	printf("[ TEST ] `GEMM`  : per   Layer    Naive  Quantization %3d/%3d\n", per_layer_cnt, TB_SIZE);
	return per_layer_cnt == TB_SIZE ? true : false;
}

bool tb_GemmPerOperationAdvanceQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                                     quantiInfo* quantInfo) {
	int per_opeation_cnt = 0;
	int tb_idx           = TB_SIZE;
	while (tb_idx--) {
		randomInit8(ipt);
		randomInit8(&opInfo->bias);
		randomInit8(&opInfo->weight);
		// ScalingFactor =  0 ~ 8
		quantInfo->scaling_factor = rand() % 8;
		// ZeroPoint =  0 ~ 127
		quantInfo->zero_point = rand() % 128;
		simd::Gemm(opt, ipt, opInfo, quantInfo, PER_OPERATION_ADVANCE_QUANTI).execute();
		scalar::Gemm(optTest, ipt, opInfo, quantInfo, PER_OPERATION_ADVANCE_QUANTI).execute();
		per_opeation_cnt += compare8(optTest, opt);
	}
	printf("[ TEST ] `GEMM`  : per Operation Advance Quantization %3d/%3d\n", per_opeation_cnt, TB_SIZE);
	return per_opeation_cnt == TB_SIZE ? true : false;
}
bool tb_GemmPerLayerAdvanceQuant(tensorInfo* optTest, tensorInfo* opt, tensorInfo* ipt, gemmInfo* opInfo,
                                 quantiInfo* quantInfo) {
	int per_layer_cnt = 0;
	int tb_idx        = TB_SIZE;
	while (tb_idx--) {
		randomInit8(ipt);
		randomInit8(&opInfo->bias);
		randomInit8(&opInfo->weight);
		// ScalingFactor =  0 ~ 8
		quantInfo->scaling_factor = rand() % 8;
		// ZeroPoint =  0 ~ 127
		quantInfo->zero_point = rand() % 128;
		simd::Gemm(opt, ipt, opInfo, quantInfo, PER_LAYER_ADVANCE_QUANTI).execute();
		scalar::Gemm(optTest, ipt, opInfo, quantInfo, PER_LAYER_ADVANCE_QUANTI).execute();
		per_layer_cnt += compare8(optTest, opt);
	}
	printf("[ TEST ] `GEMM`  : per   Layer   Advance Quantization %3d/%3d\n", per_layer_cnt, TB_SIZE);
	return per_layer_cnt == TB_SIZE ? true : false;
}
bool tb_Gemm(testType type) {
	int8_t ipt[GEMM_dimM * GEMM_dimK]     = {0};
	int8_t wgt[GEMM_dimK * GEMM_dimN]     = {0};
	int8_t opt[GEMM_dimM * GEMM_dimN]     = {0};
	int8_t optTest[GEMM_dimM * GEMM_dimN] = {0};
	int8_t bias[GEMM_dimM * GEMM_dimN]    = {0};

	tensorInfo data0     = {.N = 1, .C = 1, .H = GEMM_dimM, .W = GEMM_dimK, .data = ipt};
	tensorInfo data1     = {.N = 1, .C = 1, .H = GEMM_dimM, .W = GEMM_dimN, .data = opt};
	tensorInfo data1Test = {.N = 1, .C = 1, .H = GEMM_dimM, .W = GEMM_dimN, .data = optTest};
	tensorInfo gemmWgt   = {.N = 1, .C = 1, .H = GEMM_dimK, .W = GEMM_dimN, .data = wgt};
	tensorInfo gemmBias  = {.N = 1, .C = 1, .H = GEMM_dimM, .W = GEMM_dimN, .data = bias};
	quantiInfo qInfo     = {.scaling_factor = 0, .zero_point = 0};
	gemmInfo   gInfo     = {.weight = gemmWgt, .bias = gemmBias};

	if (type == testType::HW)
		// return tb_GemmPerOperationrNaiveQuant(&data1Test, &data1, &data0, &gInfo, &qInfo) &
		//        tb_GemmPerLayerNaiveQuant(&data1Test, &data1, &data0, &gInfo, &qInfo) &
		//        tb_GemmPerOperationAdvanceQuant(&data1Test, &data1, &data0, &gInfo, &qInfo) &
		//        tb_GemmPerLayerAdvanceQuant(&data1Test, &data1, &data0, &gInfo, &qInfo);
		return tb_GemmPerLayerAdvanceQuant(&data1Test, &data1, &data0, &gInfo, &qInfo);
	else
		return tb_GemmPerOperationrNaiveQuant(&data1Test, &data1, &data0, &gInfo, &qInfo);
}

}  // namespace tb
}  // namespace acal_lab
