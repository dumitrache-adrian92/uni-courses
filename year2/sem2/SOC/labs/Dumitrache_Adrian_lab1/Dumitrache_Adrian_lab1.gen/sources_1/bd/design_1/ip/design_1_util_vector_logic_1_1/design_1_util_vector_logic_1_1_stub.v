// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Tue Mar  7 14:34:46 2023
// Host        : Lenovo-EF001 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/student/Documents/Dumitrache_Adrian_lab1/Dumitrache_Adrian_lab1.gen/sources_1/bd/design_1/ip/design_1_util_vector_logic_1_1/design_1_util_vector_logic_1_1_stub.v
// Design      : design_1_util_vector_logic_1_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "util_vector_logic_v2_0_2_util_vector_logic,Vivado 2022.1" *)
module design_1_util_vector_logic_1_1(Op1, Op2, Res)
/* synthesis syn_black_box black_box_pad_pin="Op1[0:0],Op2[0:0],Res[0:0]" */;
  input [0:0]Op1;
  input [0:0]Op2;
  output [0:0]Res;
endmodule
