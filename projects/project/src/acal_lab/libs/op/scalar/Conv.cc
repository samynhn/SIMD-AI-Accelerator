#include "acal_lab/includes/op/scalar/Conv.h"
namespace acal_lab {
namespace scalar {

void Conv::execPerLayerNaiveQuant() {
	int16_t tempINT16_Buffer[100000] = {0};

	for (int n = 0; n < info->kernel.N; n++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				output->data[n * output->H * output->W + oh * output->W + ow] = info->bias.data[n];
				for (int c = 0; c < info->kernel.C; c++) {
					for (int kh = 0; kh < info->kernel.H; kh++) {
						for (int kw = 0; kw < info->kernel.W; kw++) {
							int16_t temp =
							    (int16_t)input->data[c * input->H * input->W + (oh + kh) * input->W + (ow + kw)] *
							    (int16_t)info->kernel
							        .data[((n * info->kernel.C + c) * info->kernel.H + kh) * info->kernel.W + kw];
							tempINT16_Buffer[n * output->H * output->W + oh * output->W + ow] += temp;
						}
					}
				}

			}
		}
	}
	// int idx = 0;
	// for (int n = 0; n < info->kernel.N; n++) {
	// 	for (int h = 0; h < output->H; h++) {
	// 		for (int w = 0; w < output->W; w++) {
	// 			idx = n * output->H * output->W + h * output->W + w;
	// 			output->data[idx] += (int8_t)(tempINT16_Buffer[idx] >> 8);
	// 		}
	// 	}
	// }
	int tempH = 0, tempW = 0;
	for (int n = 0; n < info->kernel.N; n++) {
		for (int h = 0; h < output->H; h++) {
			tempH = n * output->H * output->W + h * output->W;
			for (int w = 0; w < output->W; w++) {
				tempW = tempH + w;
				output->data[tempW] += (int8_t)(tempINT16_Buffer[tempW] >> 8);
			}
		}
	}
	
}

void Conv::execPerLayerAdvanceQuant() {
	int16_t tempINT16_Buffer[100000] = {0};
	unsigned start, end;
	unsigned total = 0;
	for (int n = 0; n < info->kernel.N; n++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				output->data[n * output->H * output->W + oh * output->W + ow] = info->bias.data[n];
				for (int c = 0; c < info->kernel.C; c++) {
					for (int kh = 0; kh < info->kernel.H; kh++) {
						for (int kw = 0; kw < info->kernel.W; kw++) {
							start = perf_get_mcycle();
							int16_t temp =
							    (int16_t)input->data[c * input->H * input->W + (oh + kh) * input->W + (ow + kw)] *
							    (int16_t)info->kernel
							        .data[((n * info->kernel.C + c) * info->kernel.H + kh) * info->kernel.W + kw];
							tempINT16_Buffer[n * output->H * output->W + oh * output->W + ow] += temp;
							end = perf_get_mcycle();
	 						total += (end - start);
						}
					}
				}

			}
		}
	}
	printf("Total scalar::conv cycles: %u\n", total);
	int idx = 0;
	for (int n = 0; n < info->kernel.N; n++) {
		for (int h = 0; h < output->H; h++) {
			for (int w = 0; w < output->W; w++) {
				idx = n * output->H * output->W + h * output->W + w;
				output->data[idx] += (int8_t)((tempINT16_Buffer[idx] >> qInfo->scaling_factor) + qInfo->zero_point);
			}
		}
	}
}

void Conv::execPerOperationNaiveQuant() {
	// Perform convolution with bias
	for (int n = 0; n < info->kernel.N; n++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				output->data[n * output->H * output->W + oh * output->W + ow] = info->bias.data[n];
				for (int c = 0; c < info->kernel.C; c++) {
					for (int kh = 0; kh < info->kernel.H; kh++) {
						for (int kw = 0; kw < info->kernel.W; kw++) {
							int16_t temp =
							    (int16_t)input->data[c * input->H * input->W + (oh + kh) * input->W + (ow + kw)] *
							    (int16_t)info->kernel
							        .data[((n * info->kernel.C + c) * info->kernel.H + kh) * info->kernel.W + kw];
							output->data[n * output->H * output->W + oh * output->W + ow] += (int8_t)(temp >> 8);
						}
					}
				}
			}
		}
	}
}

void Conv::execPerOperationAdvanceQuant() {}

}  // namespace scalar
}  // namespace acal_lab
