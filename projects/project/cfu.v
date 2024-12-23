`include "chisel/build/SIMDEngine.v"

module Cfu (
  input               cmd_valid,
  output              cmd_ready,
  input      [9:0]    cmd_payload_function_id,
  input      [31:0]   cmd_payload_inputs_0,
  input      [31:0]   cmd_payload_inputs_1,
  output              rsp_valid,
  input               rsp_ready,
  output     [31:0]   rsp_payload_outputs_0,
  input               reset,
  input               clk
);


  SIMDEngine simd(
    .clock(clk),
    .reset(reset),
    .io_cmd_payload_ready(cmd_ready),
    .io_cmd_payload_valid(cmd_valid),
    .io_cmd_payload_bits_funct7(cmd_payload_function_id[9:3]),
    .io_cmd_payload_bits_funct3(cmd_payload_function_id[2:0]),
    .io_cmd_payload_bits_rs1(cmd_payload_inputs_0),
    .io_cmd_payload_bits_rs2(cmd_payload_inputs_1),
    .io_rsp_payload_ready(rsp_ready),
    .io_rsp_payload_valid(rsp_valid),
    .io_rsp_payload_bits_rd(rsp_payload_outputs_0)
  );

endmodule
