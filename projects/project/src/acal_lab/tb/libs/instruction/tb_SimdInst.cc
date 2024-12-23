#include "acal_lab/tb/includes/instruction/tb_SimdInst.h"

#define TB_SIZE 100

namespace acal_lab {
namespace tb {

/******************************************************************************
 *                       8-2.1-1 : Signed Integer Addition                    *
 ******************************************************************************/

// 8-2.1-1.1 : Signed Integer Addition : sADDI8I8S_vv
// inline void sADDI8I8S_vv(int8_t c[4], int8_t a[4], int8_t b[4])
bool tb_sADDI8I8S_vv() {
	int8_t rs1[4], rs2[4], rd[4], rd_tb[4];
	int    idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i8_vv(rs1, rs2, rd, rd_tb);
		i8i8_alu_vv(ADD, rd_tb, rs1, rs2, 0, 0);
		sADDI8I8S_vv(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sADDI8I8S_vv`     :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-1.2 : Signed Integer Addition : sADDI16I16S_vv
// inline void sADDI16I16S_vv(int16_t c[2], int16_t a[2], int16_t b[2])
bool tb_sADDI16I16S_vv() {
	int16_t rs1[2], rs2[2], rd[2], rd_tb[2];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i16i16_vv(rs1, rs2, rd, rd_tb);
		i16i16_alu_vv(ADD, rd_tb, rs1, rs2, 0, 0);
		sADDI16I16S_vv(rd, rs1, rs2);
		cnt += i16_check(rd, rd_tb);
	}
	printf("[ TEST ] `sADDI16I16S_vv`   :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-1.3 : Signed Integer Addition : sADDI8I8S_vx
// inline void sADDI8I8S_vx(int8_t c[4], int8_t a[4], int8_t b)
bool tb_sADDI8I8S_vx() {
	int8_t rs1[4], rd[4], rd_tb[4];
	int8_t rs2;
	int    idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i8_vx(rs1, &rs2, rd, rd_tb);
		i8i8_alu_vx(ADD, rd_tb, rs1, rs2, 0, 0);
		sADDI8I8S_vx(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sADDI8I8S_vx`     :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-1.4 : Signed Integer Addition : sADDI16I16S_vx
// inline void sADDI16I16S_vx(int16_t c[2], int16_t a[2], int16_t b)
bool tb_sADDI16I16S_vx() {
	int16_t rs1[2], rd[2], rd_tb[2];
	int16_t rs2;
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i16i16_vx(rs1, &rs2, rd, rd_tb);
		i16i16_alu_vx(ADD, rd_tb, rs1, rs2, 0, 0);
		sADDI16I16S_vx(rd, rs1, rs2);
		cnt += i16_check(rd, rd_tb);
	}
	printf("[ TEST ] `sADDI16I16S_vx`   :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

bool tb_sADDS_vv() { return tb_sADDI8I8S_vv() & tb_sADDI16I16S_vv(); }
bool tb_sADDS_vx() { return tb_sADDI8I8S_vx() & tb_sADDI16I16S_vx(); }
bool tb_sADDS() { return tb_sADDS_vv() & tb_sADDS_vx(); }

/******************************************************************************
 *                     8-2.1-2 : Signed Integer Substration                   *
 ******************************************************************************/

// 8-2.1-2.1 : Signed Integer Substration : sSUBI8I8S_vv
// inline void sSUBI8I8S_vv(int8_t c[4], int8_t a[4], int8_t b[4])
bool tb_sSUBI8I8S_vv() {
	int8_t rs1[4], rs2[4], rd[4], rd_tb[4];
	int    idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i8_vv(rs1, rs2, rd, rd_tb);
		i8i8_alu_vv(SUB, rd_tb, rs1, rs2, 0, 0);
		sSUBI8I8S_vv(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sSUBI8I8S_vv`     :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-2.2 : Signed Integer Substration : sSUBI16I16S_vv
// inline void sSUBI16I16S_vv(int16_t c[2], int16_t a[2], int16_t b[2])
bool tb_sSUBI16I16S_vv() {
	int16_t rs1[2], rs2[2], rd[2], rd_tb[2];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i16i16_vv(rs1, rs2, rd, rd_tb);
		i16i16_alu_vv(SUB, rd_tb, rs1, rs2, 0, 0);
		sSUBI16I16S_vv(rd, rs1, rs2);
		cnt += i16_check(rd, rd_tb);
	}
	printf("[ TEST ] `sSUBI16I16S_vv`   :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-2.3 : Signed Integer Substration : sSUBI8I8S_vx
// inline void sSUBI8I8S_vx(int8_t c[4], int8_t a[4], int8_t b)
bool tb_sSUBI8I8S_vx() {
	int8_t rs1[4], rd[4], rd_tb[4];
	int8_t rs2;
	int    idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i8_vx(rs1, &rs2, rd, rd_tb);
		i8i8_alu_vx(SUB, rd_tb, rs1, rs2, 0, 0);
		sSUBI8I8S_vx(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sSUBI8I8S_vx`     :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-2.4 : Signed Integer Substration : sSUBI16I16S_vx
// inline void sSUBI16I16S_vx(int16_t c[2], int16_t a[2], int16_t b)
bool tb_sSUBI16I16S_vx() {
	int16_t rs1[2], rd[2], rd_tb[2];
	int16_t rs2;
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i16i16_vx(rs1, &rs2, rd, rd_tb);
		i16i16_alu_vx(SUB, rd_tb, rs1, rs2, 0, 0);
		sSUBI16I16S_vx(rd, rs1, rs2);
		cnt += i16_check(rd, rd_tb);
	}
	printf("[ TEST ] `sSUBI16I16S_vx`   :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

bool tb_sSUBS_vv() { return tb_sSUBI8I8S_vv() & tb_sSUBI16I16S_vv(); }
bool tb_sSUBS_vx() { return tb_sSUBI8I8S_vx() & tb_sSUBI16I16S_vx(); }
bool tb_sSUBS() { return tb_sSUBS_vv() & tb_sSUBS_vx(); }

/******************************************************************************
 *        8-2.1-3 : Signed Integer Precise(Lossless) Multiplication           *
 ******************************************************************************/

// 8-2.1-3.1 : Signed Integer Precise(Lossless) Multiplication :
// sPMULI8I16S_vv_L inline void sPMULI8I16S_vv_L(int16_t c[2], int8_t a[4],
// int8_t b[4])

bool tb_sPMULI8I16S_vv_L() {
	int8_t  rs1[4], rs2[4];
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vv(rs1, rs2, rd, rd_tb);
		i8i16_alu_vv(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vv_L(rd, rs1, rs2);
		cnt += i16_check(rd, rd_tb);
	}
	printf("[ TEST ] `sPMULI8I16S_vv_L` : only .L                 %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vv_H() {
	int8_t  rs1[4], rs2[4];
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vv(rs1, rs2, rd, rd_tb);
		i8i16_alu_vv(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vv_H(rd + 2, rs1, rs2);
		cnt += i16_check(rd + 2, rd_tb + 2);
	}
	printf("[ TEST ] `sPMULI8I16S_vv_H` : only .H                 %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vv_HL() {
	int8_t  rs1[4], rs2[4];
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vv(rs1, rs2, rd, rd_tb);
		i8i16_alu_vv(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vv_H(rd + 2, rs1, rs2);
		sPMULI8I16S_vv_L(rd, rs1, rs2);
		cnt += (i16_check(rd, rd_tb) + i16_check(rd + 2, rd_tb + 2) == 2) ? 1 : 0;
	}
	printf("[ TEST ] `sPMULI8I16S_vv`   : .H Before .L            %3d/%3d\n", cnt, TB_SIZE);

	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vv_LH() {
	int8_t  rs1[4], rs2[4];
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vv(rs1, rs2, rd, rd_tb);
		i8i16_alu_vv(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vv_L(rd, rs1, rs2);
		sPMULI8I16S_vv_H(rd + 2, rs1, rs2);
		cnt += (i16_check(rd, rd_tb) + i16_check(rd + 2, rd_tb + 2) == 2) ? 1 : 0;
	}
	printf("[ TEST ] `sPMULI8I16S_vv`   : .L Before .H            %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vx_L() {
	int8_t  rs1[4];
	int16_t rd[4], rd_tb[4];
	int8_t  rs2 = 0;
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vx(rs1, &rs2, rd, rd_tb);
		i8i16_alu_vx(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vx_L(rd, rs1, rs2);
		cnt += i16_check(rd, rd_tb);
	}
	printf("[ TEST ] `sPMULI8I16S_vx_L` : only .L                 %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vx_H() {
	int8_t  rs1[4];
	int8_t  rs2 = 0;
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vx(rs1, &rs2, rd, rd_tb);
		i8i16_alu_vx(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vx_H(rd + 2, rs1, rs2);
		cnt += i16_check(rd + 2, rd_tb + 2);
	}
	printf("[ TEST ] `sPMULI8I16S_vx_H` : only .H                 %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vx_LH() {
	int8_t  rs1[4];
	int8_t  rs2 = 0;
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vx(rs1, &rs2, rd, rd_tb);
		i8i16_alu_vx(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vx_L(rd, rs1, rs2);
		sPMULI8I16S_vx_H(rd + 2, rs1, rs2);
		cnt += (i16_check(rd, rd_tb) + i16_check(rd + 2, rd_tb + 2) == 2) ? 1 : 0;
	}
	printf("[ TEST ] `sPMULI8I16S_vx`   : .L Before .H            %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vx_HL() {
	int8_t  rs1[4];
	int8_t  rs2 = 0;
	int16_t rd[4], rd_tb[4];
	int     idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i16_vx(rs1, &rs2, rd, rd_tb);

		i8i16_alu_vx(PMUL, rd_tb, rs1, rs2, 0, 0);
		sPMULI8I16S_vx_H(rd + 2, rs1, rs2);
		sPMULI8I16S_vx_L(rd, rs1, rs2);
		// sPMULI8I16S_vx(rd, rs1, rs2);
		cnt += (i16_check(rd, rd_tb) + i16_check(rd + 2, rd_tb + 2) == 2) ? 1 : 0;
	}
	printf("[ TEST ] `sPMULI8I16S_vx`   : .H Before .L            %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sPMULI8I16S_vv() {
	return tb_sPMULI8I16S_vv_L() & tb_sPMULI8I16S_vv_H() & tb_sPMULI8I16S_vv_LH() & tb_sPMULI8I16S_vv_HL();
}
bool tb_sPMULI8I16S_vx() {
	return tb_sPMULI8I16S_vx_L() & tb_sPMULI8I16S_vx_H() & tb_sPMULI8I16S_vx_LH() & tb_sPMULI8I16S_vx_HL();
}
bool tb_sPMULI8I16S() { return tb_sPMULI8I16S_vv() & tb_sPMULI8I16S_vx(); }

/******************************************************************************
 *         8-2.1-4 : Signed Integer Approximate(Lossy) Multiplication         *
 ******************************************************************************/

// 8-2.1-4.1 : Signed Integer Approximate(Lossy) MUL w/ Naive Quantization :
// sAMULI8I8S_vv_NQ inline void sAMULI8I8S_vv_NQ(int8_t c[4], int8_t a[4],
// int8_t b[4])
bool tb_sAMULI8I8S_vv_NQ() {
	int8_t rs1[4], rs2[4], rd[4], rd_tb[4];
	int    idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i8_vv(rs1, rs2, rd, rd_tb);
		i8i8_alu_vv(AMULNQ, rd_tb, rs1, rs2, 0, 0);
		sAMULI8I8S_vv_NQ(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sAMULI8I8S_vv_NQ` :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-4.2 : Signed Integer Approximate(Lossy) MUL w/ Advance Quantization :
// sAMULI8I8S_vv_AQ inline void sAMULI8I8S_vv_AQ(int8_t c[4], int8_t a[4],
// int8_t b[4])
bool tb_sAMULI8I8S_vv_AQ() {
	int8_t rs1[4], rs2[4], rd[4], rd_tb[4];
	int    idx = TB_SIZE, cnt = 0;
	int    sc = 0, zpt = 0;

	while (idx--) {
		// ScalingFactor =  0 ~ 8
		sc = rand() % 8;
		// ZeroPoint = 0 ~ 127
		zpt = rand() % 128;
		randinit_i8i8_vv(rs1, rs2, rd, rd_tb);
		i8i8_alu_vv(AMULAQ, rd_tb, rs1, rs2, sc, zpt);
		sQNT_INFO(sc, zpt);
		sAMULI8I8S_vv_AQ(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sAMULI8I8S_vv_AQ` :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-4.3 : Signed Integer Approximate(Lossy) MUL w/ Naive Quantization :
// sAMULI8I8S_vx_NQ inline void sAMULI8I8S_vx_NQ(int8_t c[4], int8_t a[4],
// int8_t b)
bool tb_sAMULI8I8S_vx_NQ() {
	int8_t rs1[4], rd[4], rd_tb[4];
	int8_t rs2;
	int    idx = TB_SIZE, cnt = 0;
	while (idx--) {
		randinit_i8i8_vx(rs1, &rs2, rd, rd_tb);
		i8i8_alu_vx(AMULNQ, rd_tb, rs1, rs2, 0, 0);
		sAMULI8I8S_vx_NQ(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sAMULI8I8S_vx_NQ` :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}

// 8-2.1-4.4 : Signed Integer Approximate(Lossy) MUL w/ Advance Quantization :
// sAMULI8I8S_vx_AQ inline void sAMULI8I8S_vx_AQ(int8_t c[4], int8_t a[4],
// int8_t b[4])
bool tb_sAMULI8I8S_vx_AQ() {
	int8_t rs1[4], rd[4], rd_tb[4];
	int8_t rs2;
	int    idx = TB_SIZE, cnt = 0;
	int    sc = 0, zpt = 0;
	while (idx--) {
		// ScalingFactor =  0 ~ 8
		sc = rand() % 8;
		// ZeroPoint = 0 ~ 127
		zpt = rand() % 128;
		randinit_i8i8_vx(rs1, &rs2, rd, rd_tb);
		i8i8_alu_vx(AMULAQ, rd_tb, rs1, rs2, sc, zpt);
		sQNT_INFO(sc, zpt);
		sAMULI8I8S_vx_AQ(rd, rs1, rs2);
		cnt += i8_check(rd, rd_tb);
	}
	printf("[ TEST ] `sAMULI8I8S_vx_AQ` :                         %3d/%3d\n", cnt, TB_SIZE);
	return cnt == TB_SIZE;
}
bool tb_sAMULI8I8S_vv() { return tb_sAMULI8I8S_vv_NQ() & tb_sAMULI8I8S_vv_AQ(); }
bool tb_sAMULI8I8S_vx() { return tb_sAMULI8I8S_vx_NQ() & tb_sAMULI8I8S_vx_AQ(); }
bool tb_sAMULI8I8S() { return tb_sAMULI8I8S_vv() & tb_sAMULI8I8S_vx(); }

}  // namespace tb
}  // namespace acal_lab
