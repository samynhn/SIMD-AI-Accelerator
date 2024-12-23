#include "acal_lab/tb/includes/instruction/tb_SoftwareALU.h"
namespace acal_lab {
namespace tb {

void i8i8_alu_vv(operation op, int8_t rd[4], int8_t rs1[4], int8_t rs2[4], int sc, int zpt) {
	int idx = 4;
	while (idx--) {
		switch (op) {
			case ADD: rd[idx] = rs1[idx] + rs2[idx]; break;
			case SUB: rd[idx] = rs1[idx] - rs2[idx]; break;
			case AMULNQ: rd[idx] = (int8_t)(((int16_t)rs1[idx] * (int16_t)rs2[idx]) >> 8); break;
			case AMULAQ: rd[idx] = (int8_t)((((int16_t)rs1[idx] * (int16_t)rs2[idx]) >> sc) + zpt); break;
			default: break;
		}
	}
	return;
}

void i8i8_alu_vx(operation op, int8_t rd[4], int8_t rs1[4], int32_t rs2, int sc, int zpt) {
	int idx = 4;
	while (idx--) {
		switch (op) {
			case ADD: rd[idx] = rs1[idx] + (int8_t)rs2; break;
			case SUB: rd[idx] = rs1[idx] - (int8_t)rs2; break;
			case AMULNQ: rd[idx] = (int8_t)(((int16_t)rs1[idx] * (int16_t)rs2) >> 8); break;
			case AMULAQ: rd[idx] = (int8_t)((((int16_t)rs1[idx] * (int16_t)rs2) >> sc) + zpt); break;
			default: break;
		}
	}
	return;
}

void i16i16_alu_vv(operation op, int16_t rd[2], int16_t rs1[2], int16_t rs2[2], int sc, int zpt) {
	int idx = 2;
	while (idx--) {
		switch (op) {
			case ADD: rd[idx] = rs1[idx] + rs2[idx]; break;
			case SUB: rd[idx] = rs1[idx] - rs2[idx]; break;
			default: break;
		}
	}
	return;
}

void i16i16_alu_vx(operation op, int16_t rd[2], int16_t rs1[2], int32_t rs2, int sc, int zpt) {
	int idx = 2;
	while (idx--) {
		switch (op) {
			case ADD: rd[idx] = rs1[idx] + (int16_t)rs2; break;
			case SUB: rd[idx] = rs1[idx] - (int16_t)rs2; break;
			default: break;
		}
	}
	return;
}

void i8i16_alu_vv(operation op, int16_t rd[4], int8_t rs1[4], int8_t rs2[4], int sc, int zpt) {
	int idx = 4;
	while (idx--) {
		switch (op) {
			case PMUL: rd[idx] = (int16_t)rs1[idx] * (int16_t)rs2[idx]; break;
			default: break;
		}
	}
	return;
}

void i8i16_alu_vx(operation op, int16_t rd[4], int8_t rs1[4], int32_t rs2, int sc, int zpt) {
	int idx = 4;
	while (idx--) {
		switch (op) {
			case PMUL: rd[idx] = (int16_t)rs1[idx] * (int16_t)rs2; break;
			default: break;
		}
	}
	return;
}

}  // namespace tb
}  // namespace acal_lab
