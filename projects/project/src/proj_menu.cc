/*
 * Copyright 2021 The CFU-Playground Authors
 * Copyright (c) 2023 Playlab, National Cheng Kung University.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "proj_menu.h"

#include <stdio.h>

#include "acal_lab/tb/includes/instruction.h"
#include "acal_lab/tb/includes/models.h"
#include "acal_lab/tb/includes/op.h"
#include "cfu.h"
#include "menu.h"

using namespace acal_lab;

namespace {

void do_SIMD_TB_lab(void) {
	printf("=================   SIMD Vector-Vector   ====================\n");
	bool vvTB = tb::tb_sADDS_vv() & tb::tb_sSUBS_vv() & tb::tb_sPMULI8I16S_vv() & tb::tb_sAMULI8I8S_vv_NQ();
	printf("-------------------------------------------------------------\n");
	printf("SIMD Integer Extension : (Lab Edition)                 | %4s\n", vvTB ? "Pass" : "Fail");
	printf("=============================================================\n");
}

void do_SIMD_TB_hw(void) {
	printf("=================   SIMD Vector-Vector   ====================\n");
	bool vvTB = tb::tb_sADDS_vv() & tb::tb_sSUBS_vv() & tb::tb_sPMULI8I16S_vv() & tb::tb_sAMULI8I8S_vv();
	printf("-------------------------------------------------------------\n");
	printf("=> SUMMARY | SIMD Vector-Vector :                     | %4s\n", vvTB ? "Pass" : "Fail");
	printf("=================   SIMD Vector-Vector   ====================\n");
	bool vxTB = tb::tb_sADDS_vx() & tb::tb_sSUBS_vx() & tb::tb_sPMULI8I16S_vx() & tb::tb_sAMULI8I8S_vx();
	printf("-------------------------------------------------------------\n");
	printf("=> SUMMARY | SIMD Vector-Scalar :                     | %4s\n", vxTB ? "Pass" : "Fail");
	printf("-------------------------------------------------------------\n");
	printf("SIMD Integer Extension : (Homework Edition)           | %4s\n", vvTB & vxTB ? "Pass" : "Fail");
	printf("=============================================================\n");
}

void do_GEMM_with_SIMD_lab(void) {
	printf("===================   GEMM with SIMD   ======================\n");
	printf(
	    "-------------------------------------------------------------\n"
	    "`GEMM` with SIMD (LAB Edition)                         | %4s\n",
	    tb::tb_Gemm(tb::testType::LAB) ? "Pass" : "Fail");
}

void do_GEMM_with_SIMD_hw(void) {
	printf("===================   GEMM with SIMD   ======================\n");
	printf(
	    "-------------------------------------------------------------\n"
	    "`GEMM` with SIMD (Homework Edition)                    | %4s\n",
	    tb::tb_Gemm(tb::testType::HW) ? "Pass" : "Fail");
}

void do_CONV_with_SIMD_hw(void) {
	printf("===================   CONV with SIMD   ======================\n");
	printf("... It may take some time\n");
	printf(
	    "-------------------------------------------------------------\n"
	    "`CONV` with SIMD (Homework Edition)                    | %4s\n",
	    tb::tb_Conv(tb::testType::HW) ? "Pass" : "Fail");
}

void do_MXPL_with_SIMD_hw(void) {
	printf("===================   MXPL with SIMD   ======================\n");
	printf(
	    "-------------------------------------------------------------\n"
	    "`MXPL` with SIMD (Homework Edition)                    | %4s\n",
	    tb::tb_MxPl() ? "Pass" : "Fail");
}

void do_RELU_with_SIMD_hw(void) {
	printf("===================   RELU with SIMD   ======================\n");
	printf(
	    "-------------------------------------------------------------\n"
	    "`RELU` with SIMD (Homework Edition)                    | %4s\n",
	    tb::tb_ReLU() ? "Pass" : "Fail");
}

void do_OP_with_SIMD_hw(void) {
	do_GEMM_with_SIMD_hw();
	do_CONV_with_SIMD_hw();
	do_MXPL_with_SIMD_hw();
	do_RELU_with_SIMD_hw();
	printf("=============================================================\n");
}

void do_ALEXNET_INFERENCE_DATA0(void) {
	printf("=====================   AlexNet with SIMD   =================\n");
	printf("data0 in AlexNet (Homework Edition)                    | %4s\n",
	       tb::tb_AlexNet(tb::testbench::PICTURE_0) ? "Pass" : "Fail");
	printf("-------------------------------------------------------------\n");
}

void do_ALEXNET_INFERENCE_DATA1(void) {
	printf("=====================   AlexNet with SIMD   =================\n");
	printf("data1 in AlexNet (Homework Edition)                    | %4s\n",
	       tb::tb_AlexNet(tb::testbench::PICTURE_1) ? "Pass" : "Fail");
	printf("-------------------------------------------------------------\n");
}
void do_ALL() {
	do_SIMD_TB_hw();
	printf("\n\n");
	do_GEMM_with_SIMD_hw();
	do_CONV_with_SIMD_hw();
	do_MXPL_with_SIMD_hw();
	do_RELU_with_SIMD_hw();
	do_ALEXNET_INFERENCE_DATA0();
	do_ALEXNET_INFERENCE_DATA1();
}

struct Menu MENU = {
    "Project Menu",
    "project",
    {
        MENU_ITEM('0', "test SIMD instruction - Integer Extension (Lab Edition)", do_SIMD_TB_lab),
        MENU_ITEM('1', "test SIMD instruction - Integer Extension (Homework Edidtion)", do_SIMD_TB_hw),
        MENU_ITEM('a', "test GEMM Operator    - with SIMD Extension (Lab Edition)", do_GEMM_with_SIMD_lab),
        MENU_ITEM('b', "test GEMM Operator    - with SIMD Extension (Homework Edition)", do_GEMM_with_SIMD_hw),
        MENU_ITEM('c', "test CONV Operator    - with SIMD Extension (Homework Edition)", do_CONV_with_SIMD_hw),
        MENU_ITEM('d', "test MXPL Operator    - with SIMD Extension (Homework Edition)", do_MXPL_with_SIMD_hw),
        MENU_ITEM('e', "test RELU Operator    - with SIMD Extension (Homework Edition)", do_RELU_with_SIMD_hw),
        MENU_ITEM('f', "test ALL  Operator    - with SIMD Extension (Homework Edition)", do_OP_with_SIMD_hw),
        MENU_ITEM('g', "test AlexNet (data0)  - with SIMD Extension (Homework Edition)", do_ALEXNET_INFERENCE_DATA0),
        MENU_ITEM('h', "test AlexNet (daat1)  - with SIMD Extension (Homework Edition)", do_ALEXNET_INFERENCE_DATA1),
        MENU_ITEM('i', "test All", do_ALL),
        MENU_END,
    },
};

};  // anonymous namespace

extern "C" void do_proj_menu() { menu_run(&MENU); }
