#include "acal_lab/includes/op/simd/MxPl.h"
namespace acal_lab {
namespace simd {

void MxPl::exec() {
    int8_t temp_A[4] = {0}, temp_B[4] = {0}, temp_C[4] = {0};
	unsigned start, end;
	unsigned total = 0;

    for (int c = 0; c < output->C; c++) {
		for (int oh = 0; oh < output->H; oh++) {
			for (int ow = 0; ow < output->W; ow++) {
				int    input_start_h = oh * info->stride - info->padding;
				int    input_start_w = ow * info->stride - info->padding;
				int8_t max_val       = INT8_MIN;
                int i = 0;
				for (int kh = 0; kh < info->kernelSize; kh++) {
					for (int kw = 0; kw < info->kernelSize; kw++) {
						int ih = input_start_h + kh;
						int iw = input_start_w + kw;
                        
						if (ih >= 0 && ih < input->H && iw >= 0 && iw < input->W) {
							temp_A[i] = input->data[c * input->H * input->W + ih * input->W + iw];
                            temp_B[i] = max_val;
                            i++;
						}
					}
				}
				start = perf_get_mcycle();
                sSCMPLE8((int8_t*)temp_C, (int8_t*)temp_A, (int8_t*)temp_B);
                for (int x = 0; x < 4; x++){
                    if (temp_C[x] > max_val)
                        max_val = temp_C[x];
                }
				end = perf_get_mcycle();
    			total += (end - start);
				output->data[c * output->H * output->W + oh * output->W + ow] = max_val;
			}
		}
	}
	printf("Total simd::MxPl cycles: %u\n", total);
}
}  // namespace simd
}  // namespace acal_lab
