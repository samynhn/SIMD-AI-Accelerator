#include "acal_lab/includes/op/simd/Conv.h"
namespace acal_lab {
namespace simd {

void Conv::execPerLayerNaiveQuant() {
	/********************************************************************
	 * TODO:                                                            *
	 * For Homework 13.4, your task is to implement CONV with per Layer *
	 * `Naive Quantization`. This involves using the instruction        *
	 * `sPMULI8I16S(.vv/.vx)` to generate int16 output. However, the    *
	 * int16 output needs to be converted to int8 and then forwarded    *
	 * to the next Operator. To achieve this, utilize `sQNTI16I8S.vv.NQ`*
	 * for the conversion.                                              *
	 *******************************************************************/
	int16_t tempINT16_Buffer[100000] = {0};
	int16_t temp_C[4] = {0}, temp_D[4] = {0};
	int8_t temp_A[4] = {0}, temp_B[4] = {0}, temp_E[4] = {0};
	
	for (int n = 0; n < info->kernel.N; n++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				output->data[n * output->H * output->W + oh * output->W + ow] = info->bias.data[n];
				for (int c = 0; c < info->kernel.C; c++) {
					for (int kh = 0; kh < info->kernel.H; kh++) {
						for (int kw = 0; kw < info->kernel.W; kw+=4) {
							for (int i = 0; i < 4; i++) {
								if (kw + i >= info->kernel.W) {
									temp_A[i] = 0;
									temp_B[i] = 0;
								}else{
									temp_A[i] = input->data[c * input->H * input->W + (oh + kh) * input->W + (ow + kw + i)];
									temp_B[i] = info->kernel.data[((n * info->kernel.C + c) * info->kernel.H + kh) * info->kernel.W + kw + i];
								}
							}
							sPMULI8I16S_vv_L(temp_C, temp_A, temp_B);
							sPMULI8I16S_vv_H(temp_C+2, temp_A, temp_B);
							for (int i = 0; i < 4; i++)
								tempINT16_Buffer[n * output->H * output->W + oh * output->W + ow] += temp_C[i];
								
						}
					}
				}
			}
		}
	}

	int tempH = 0, tempW = 0;
	for (int n = 0; n < info->kernel.N; n++) {
		for (int h = 0; h < output->H; h++) {
			tempH = n * output->H * output->W + h * output->W;
			for (int w = 0; w < output->W; w+=4) {
				tempW = tempH + w;
				for (int i = 0; i < 4; i++){
					temp_D[i] = tempINT16_Buffer[tempW+i];
				}
				sQNTI16I8S_vv_NQ(temp_E, temp_D, temp_D+2);
				for (int i = 0; i < 4; i++){
					if (w + i < output->W)
						output->data[tempW+i] += temp_E[i];
				}
			}
		}
	}
	
}

void Conv::execPerLayerAdvanceQuant() {
	/***********************************************************
	 * TODO:                                                   *
	 * For Homework 13.4, implement CONV with per Operation    *
	 * `Advance Quantization`. Update instruction in the       *
	 * `void acal_lab::Conv::execPerLayerNaiveQuant()`         *
	 * function from `sQNTI16I8S.vv.NQ` to `sQNTI16I8S.vv.AQ`. *
	 **********************************************************/
	int16_t tempINT16_Buffer[100000] = {0};
	int16_t temp_C[4] = {0}, temp_D[4] = {0};
	int8_t temp_A[4] = {0}, temp_B[4] = {0}, temp_E[4] = {0};
	unsigned start, end;
	unsigned total = 0;

	for (int n = 0; n < info->kernel.N; n++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				output->data[n * output->H * output->W + oh * output->W + ow] = info->bias.data[n];
				for (int c = 0; c < info->kernel.C; c++) {
					for (int kh = 0; kh < info->kernel.H; kh++) {
						for (int kw = 0; kw < info->kernel.W; kw+=4) {
							for (int i = 0; i < 4; i++) {
								if (kw + i >= info->kernel.W) {
									temp_A[i] = 0;
									temp_B[i] = 0;
								}else{
									temp_A[i] = input->data[c * input->H * input->W + (oh + kh) * input->W + (ow + kw + i)];
									temp_B[i] = info->kernel.data[((n * info->kernel.C + c) * info->kernel.H + kh) * info->kernel.W + kw + i];
								}
							}
							start = perf_get_mcycle();
							sPMULI8I16S_vv_L(temp_C, temp_A, temp_B);
							sPMULI8I16S_vv_H(temp_C+2, temp_A, temp_B);
							// end = perf_get_mcycle();
    						// total += (end - start);
							for (int i = 0; i < 4; i++)
								tempINT16_Buffer[n * output->H * output->W + oh * output->W + ow] += temp_C[i];
							end = perf_get_mcycle();
    						total += (end - start);
						}
					}
				}
			}
		}
	}
	printf("Total simd::conv cycles: %u\n", total);
	sQNT_INFO(qInfo->scaling_factor, qInfo->zero_point);
	int tempH = 0, tempW = 0;
	for (int n = 0; n < info->kernel.N; n++) {
		for (int h = 0; h < output->H; h++) {
			tempH = n * output->H * output->W + h * output->W;
			for (int w = 0; w < output->W; w+=4) {
				tempW = tempH + w;
				for (int i = 0; i < 4; i++){
					temp_D[i] = tempINT16_Buffer[tempW+i];
				}
				sQNTI16I8S_vv_AQ(temp_E, temp_D, temp_D+2);
				for (int i = 0; i < 4; i++){
					if (w + i < output->W)
						output->data[tempW+i] += temp_E[i];
				}
			}
		}
	}
	
}

void Conv::execPerOperationNaiveQuant() {
	// `sAMULI8I8S(.vv/.vx).NQ`
	int8_t temp_A[4] = {0}, temp_B[4] = {0}, temp_C[4] = {0};
	unsigned start, end;
	unsigned total = 0;

	for (int n = 0; n < info->kernel.N; n++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				output->data[n * output->H * output->W + oh * output->W + ow] = info->bias.data[n];
				for (int c = 0; c < info->kernel.C; c++) {
					for (int kh = 0; kh < info->kernel.H; kh++) {
						for (int kw = 0; kw < info->kernel.W; kw+=4) {
							for (int i = 0; i < 4; i++) {
								if (kw + i >= info->kernel.W) {
									temp_A[i] = 0;
									temp_B[i] = 0;
								}else{
									temp_A[i] = input->data[c * input->H * input->W + (oh + kh) * input->W + (ow + kw + i)];
									temp_B[i] = info->kernel.data[((n * info->kernel.C + c) * info->kernel.H + kh) * info->kernel.W + kw + i];
								}
							}
							start = perf_get_mcycle();
							sAMULI8I8S_vv_NQ(temp_C, temp_A, temp_B);
							for (int i = 0; i < 4; i++)
								output->data[n * output->H * output->W + oh * output->W + ow] += temp_C[i];
							end = perf_get_mcycle();
    						total += (end - start);
						}
					}
				}
			}
		}
	}
	printf("Total simd::conv cycles: %u\n", total);
}

void Conv::execPerOperationAdvanceQuant() {
	/********************************************************
	 * TODO:                                                *
	 * For Homework 8.4, implement CONV with per Operation  *
	 * Advance Quantization. Update instruction in the      *
	 * `void acal_lab::Conv::execPerOperationNaiveQuant()`  *
	 * function from `sAMULI8I8S(.vv/.vx).NQ` to            *
	 * `sAMULI8I8S(.vv/.vx).AQ`.                            *
	 *******************************************************/
}

}  // namespace simd
}  // namespace acal_lab
