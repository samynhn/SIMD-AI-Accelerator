#include "acal_lab/tb/includes/instruction/tb_SimdUtil.h"
namespace acal_lab {
namespace tb {

void randinit_i8i8_vv(int8_t rs1[4], int8_t rs2[4], int8_t rdhw[4], int8_t rdtb[4]) {
	int idx = 4;
	while (idx--) {
		rdtb[idx] = 0;
		rdhw[idx] = 0;
		rs1[idx]  = rand() % TB_DATA_SIZE_16_BIT;
		rs2[idx]  = rand() % TB_DATA_SIZE_16_BIT;
	}
	return;
}

void randinit_i8i8_vx(int8_t rs1[4], int8_t* rs2, int8_t rdhw[4], int8_t rdtb[4]) {
	int idx = 4;
	*rs2    = rand() % TB_DATA_SIZE_16_BIT;
	while (idx--) {
		rdtb[idx] = 0;
		rdhw[idx] = 0;
		rs1[idx]  = rand() % TB_DATA_SIZE_16_BIT;
	}
	return;
}

void randinit_i16i16_vv(int16_t rs1[2], int16_t rs2[2], int16_t rdhw[2], int16_t rdtb[2]) {
	int idx = 2;
	while (idx--) {
		rdtb[idx] = 0;
		rdhw[idx] = 0;
		rs1[idx]  = rand() % (TB_DATA_SIZE_16_BIT * TB_DATA_SIZE_16_BIT);
		rs2[idx]  = rand() % (TB_DATA_SIZE_16_BIT * TB_DATA_SIZE_16_BIT);
	}
	return;
}

void randinit_i16i16_vx(int16_t rs1[2], int16_t* rs2, int16_t rdhw[2], int16_t rdtb[2]) {
	int idx = 2;
	*rs2    = rand() % (TB_DATA_SIZE_16_BIT * TB_DATA_SIZE_16_BIT);
	while (idx--) {
		rdtb[idx] = 0;
		rdhw[idx] = 0;
		rs1[idx]  = rand() % (TB_DATA_SIZE_16_BIT * TB_DATA_SIZE_16_BIT);
	}
	return;
}

void randinit_i8i16_vv(int8_t rs1[4], int8_t rs2[4], int16_t rdhw[4], int16_t rdtb[4]) {
	int idx = 4;
	while (idx--) {
		rdtb[idx] = 0;
		rdhw[idx] = 0;
		rs1[idx]  = rand() % TB_DATA_SIZE_16_BIT;
		rs2[idx]  = rand() % TB_DATA_SIZE_16_BIT;
	}
	return;
}

void randinit_i8i16_vx(int8_t rs1[4], int8_t* rs2, int16_t rdhw[4], int16_t rdtb[4]) {
	int idx = 2;
	*rs2    = rand() % TB_DATA_SIZE_16_BIT;
	while (idx--) {
		rdtb[idx] = 0;
		rdhw[idx] = 0;
		rs1[idx]  = rand() % TB_DATA_SIZE_16_BIT;
	}
	return;
}

int i8_check(int8_t rdhw[4], int8_t rdtb[4]) {
	return ((rdtb[0] == rdhw[0]) & (rdtb[1] == rdhw[1]) & (rdtb[2] == rdhw[2]) & (rdtb[3] == rdhw[3])) ? 1 : 0;
}

int i16_check(int16_t rdhw[2], int16_t rdtb[2]) { return ((rdtb[0] == rdhw[0]) & (rdtb[1] == rdhw[1])) ? 1 : 0; }

}  // namespace tb
}  // namespace acal_lab
