#include "acal_lab/tb/includes/op/simd/tb_Op.h"

namespace acal_lab {
namespace tb {

bool compare8(tensorInfo* hw, tensorInfo* tb) {
	int correct = 0;
	for (int n = 0; n < hw->N; n++)
		for (int c = 0; c < hw->C; c++)
			for (int h = 0; h < hw->H; h++)
				for (int w = 0; w < hw->W; w++) {
					int index = (((n * hw->C + c) * hw->H) + h) * hw->W + w;
					correct += ((hw->data[index] == tb->data[index]) ? 1 : 0);
				}

	return correct == (hw->C * hw->H * hw->W) ? 1 : 0;
}

void randomInit8(acal_lab::tensorInfo* tInfo) {
	for (int n = 0; n < tInfo->N; n++)
		for (int c = 0; c < tInfo->C; c++)
			for (int h = 0; h < tInfo->H; h++)
				for (int w = 0; w < tInfo->W; w++) {
					int index          = (c * tInfo->H + h) * tInfo->W + w;
					tInfo->data[index] = (int8_t)(rand() % (2 * _8_BIT_) - _8_BIT_);
				}
}

}  // namespace tb
}  // namespace acal_lab
