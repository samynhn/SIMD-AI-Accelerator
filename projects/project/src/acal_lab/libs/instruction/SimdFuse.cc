#include "acal_lab/includes/instruction/SimdFuse.h"

namespace acal_lab {
// 13-3-1-3.5 : Signed Integer Precise(Lossless) Multiplication : sPMULI8I16S_vv
inline void sPMULI8I16S_vv(int16_t c[4], int8_t a[4], int8_t b[4]) {
	sPMULI8I16S_vv_L(c, a, b);
	sPMULI8I16S_vv_H(c + 2, a, b);
}

// 13-3-1-3.6 : Signed Integer Precise(Lossless) Multiplication : sPMULI8I16S_vx
inline void sPMULI8I16S_vx(int16_t c[4], int8_t a[4], int8_t b) {
	sPMULI8I16S_vx_L(c, a, b);
	sPMULI8I16S_vx_H(c + 2, a, b);
}
}  // namespace acal_lab