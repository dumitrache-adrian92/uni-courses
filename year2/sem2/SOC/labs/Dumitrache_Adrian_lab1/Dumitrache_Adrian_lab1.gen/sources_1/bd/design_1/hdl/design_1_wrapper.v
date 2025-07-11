//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Tue Mar  7 14:28:16 2023
//Host        : Lenovo-EF001 running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (Op1_0,
    Op2_0,
    Op2_1,
    Res_0);
  input [0:0]Op1_0;
  input [0:0]Op2_0;
  input [0:0]Op2_1;
  output [0:0]Res_0;

  wire [0:0]Op1_0;
  wire [0:0]Op2_0;
  wire [0:0]Op2_1;
  wire [0:0]Res_0;

  design_1 design_1_i
       (.Op1_0(Op1_0),
        .Op2_0(Op2_0),
        .Op2_1(Op2_1),
        .Res_0(Res_0));
endmodule
