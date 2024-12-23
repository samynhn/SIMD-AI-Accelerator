#include "acal_lab/includes/op/scalar/ReLU.h"
namespace acal_lab {
namespace scalar {

void ReLU::exec() {
	int c_idx = 0, h_idx = 0, w_idx = 0;
	unsigned start, end;
	unsigned total = 0;

	for (int c = 0; c < input->C; c++) {
		c_idx = c * input->H;
		for (int h = 0; h < input->H; h++) {
			h_idx = (c_idx + h) * input->W;
			for (int w = 0; w < input->W; w++) {
				w_idx               = h_idx + w;
				start = perf_get_mcycle();
				output->data[w_idx] = input->data[w_idx] > 0 ? input->data[w_idx] : 0;
				end = perf_get_mcycle();
    			total += (end - start);
			}
		}
	}
	printf("Total scalar::ReLU cycles: %u\n", total);
}

}  // namespace scalar
}  // namespace acal_lab
