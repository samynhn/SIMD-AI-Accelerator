#include "acal_lab/includes/op/simd/Gemm.h"
#include <cstdio>
namespace acal_lab {
namespace simd {

void Gemm::execPerLayerNaiveQuant() {}

void Gemm::execPerOperationNaiveQuant() {
	int    index_A, index_B, index_C;
	int8_t temp_A[4] = {0}, temp_B[4] = {0}, temp_C[4] = {0};
	unsigned start, end;
	unsigned total = 0;
		
	for (int m = 0; m < input->H; m++) {
		index_A = m * input->W;   // M * K
		index_C = m * output->W;  // M * N
		for (int k = 0; k < input->W; k++) {
			index_B = k * info->weight.W;  // K * N
			for (int n = 0; n < info->weight.W; n += 4) {
				for (int i = 0; i < 4; ++i) temp_A[i] = input->data[index_A + k];
				*(int32_t*)temp_B = *(int32_t*)&(info->weight.data)[index_B + n];
				int output_index  = index_C + n;
				start = perf_get_mcycle();
				sAMULI8I8S_vv_NQ(temp_C, temp_A, temp_B);
				sADDI8I8S_vv((int8_t*)&(output->data[output_index]), (int8_t*)&(output->data[output_index]),
				             (int8_t*)(temp_C));
				end = perf_get_mcycle();
    			total += (end - start);
			}
			
		}
		for (int n = 0; n < info->weight.W;) {
			sADDI8I8S_vv((int8_t*)&(output->data[index_C + n]), (int8_t*)&(output->data[index_C + n]),
			             (int8_t*)&(info->bias.data[index_C + n]));
			n += 4;
		}
	}
	printf("Total simd::gemm cycles: %u\n", total);
}

void Gemm::execPerLayerAdvanceQuant() {
	/********************************************************************
	 * TODO:                                                            *
	 * For Homework 13.3, your task is to implement GEMM with per Layer *
	 * `Advance Quantization`. This involves using the instruction      *
	 * `sPMULI8I16S(.vv/.vx)` to generate int16 output. However, the    *
	 * int16 output needs to be converted to int8 and then forwarded    *
	 * to the next Operator. To achieve this, utilize `sQNTI16I8S.vv.AQ`*
	 * for the conversion.                                              *
	 *******************************************************************/
	int16_t tempINT16_Buffer[100000] = {0};
	int index_A, index_B, index_C;
	int8_t temp_A[4] = {0}, temp_B[4] = {0};
	int16_t temp_C[4] = {0}, temp_D[4] = {0};
	unsigned start, end;
	unsigned total = 0;

	for (int m = 0; m < input->H; m++) {
		index_A = m * input->W;   // M * K
		index_C = m * output->W;  // M * N
		for (int k = 0; k < input->W; k++) {
			index_B = k * info->weight.W;  // K * N
			for (int n = 0; n < info->weight.W; n += 4) {
				for (int i = 0; i < 4; ++i){
					if (n + i >= info->weight.W)
						temp_A[i] = 0;
					else
						temp_A[i] = input->data[index_A + k];
				}
				*(int32_t*)temp_B = *(int32_t*)&(info->weight.data)[index_B + n];
				int output_index = index_C + n;
				start = perf_get_mcycle();
				sPMULI8I16S_vv_L(temp_C, temp_A, temp_B);
				sPMULI8I16S_vv_H(temp_C + 2, temp_A, temp_B);
				sADDI16I16S_vv(tempINT16_Buffer + output_index, tempINT16_Buffer + output_index, temp_C);
				sADDI16I16S_vv(tempINT16_Buffer + output_index + 2, tempINT16_Buffer + output_index + 2, temp_C + 2);
				// for (int i = 0; i < 4; ++i) tempINT16_Buffer[output_index + i] += temp_C[i];

				end = perf_get_mcycle();
    			total += (end - start);
			}
		}
		for (int n = 0; n < info->weight.W; n++) tempINT16_Buffer[index_C + n] += info->bias.data[index_C + n];
	}
	printf("Total simd::gemm cycles: %u\n", total);

	sQNT_INFO(qInfo->scaling_factor, qInfo->zero_point);
	// PER LAYER QUANTIZATION
	int tempH = 0, tempW = 0;
	for (int h = 0; h < output->H; h++) {
		tempH = h * output->W;  // M * N
		for (int w = 0; w < output->W; w += 4) {
			tempW = tempH + w;
			for (int i = 0; i < 4; i++){
				if (w + i >= output->W) {
					temp_D[i] = 0;
				}else{
					temp_D[i] = tempINT16_Buffer[tempW + i];
				}
			}
			sQNTI16I8S_vv_AQ((int8_t*)&(output->data[tempW]), temp_D, temp_D+2);
		}
	}
}

void Gemm::execPerOperationAdvanceQuant() {
	/********************************************************************
	 * TODO:                                                            *
	 * For Homework 13.3, your task is to implement GEMM with per Layer *
	 * `Advance Quantization`. This involves using the instruction      *
	 * `sPMULI8I16S(.vv/.vx)` to generate int16 output. However, the    *
	 * int16 output needs to be converted to int8 and then forwarded    *
	 * to the next Operator. To achieve this, utilize `sQNTI16I8S.vv.AQ`*
	 * for the conversion.                                              *
	 *******************************************************************/
}

}  // namespace simd
}  // namespace acal_lab
