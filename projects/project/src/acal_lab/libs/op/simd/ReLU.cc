#include "acal_lab/includes/op/simd/ReLU.h"
namespace acal_lab {
namespace simd {

void ReLU::exec() {
    int c_idx = 0, h_idx = 0, w_idx = 0;
    int8_t tempA[4] = {0}, tempB[4] = {0};
    unsigned start, end;
	unsigned total = 0;
    
    for (int c = 0; c < input->C; c++) {
        c_idx = c * input->H;
        for (int h = 0; h < input->H; h++) {
            h_idx = (c_idx + h) * input->W;
            for (int w = 0; w < input->W; w+=4) {
                for (int i = 0; i < 4; i++){
                    if (w + i >= input->W)
                        tempA[i] = 0;
                    else
                        tempA[i] = input->data[h_idx + w + i];
                }
                w_idx = h_idx + w;
                start = perf_get_mcycle();
                if (w_idx % 4 ==0)
                    sSCMPLE8((int8_t*)&(output->data[w_idx]), (int8_t*)tempA, (int8_t*)tempB);
                end = perf_get_mcycle();
    			total += (end - start);
            }
        }
    }
    printf("Total simd::ReLU cycles: %u\n", total);
}
}  // namespace simd
}  // namespace acal_lab