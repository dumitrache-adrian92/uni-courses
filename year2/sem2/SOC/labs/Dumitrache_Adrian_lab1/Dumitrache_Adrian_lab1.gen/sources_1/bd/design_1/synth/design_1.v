//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Tue Mar  7 14:28:16 2023
//Host        : Lenovo-EF001 running 64-bit major release  (build 9200)
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=2,numReposBlks=2,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
   (Op1_0,
    Op2_0,
    Op2_1,
    Res_0);
  input [0:0]Op1_0;
  input [0:0]Op2_0;
  input [0:0]Op2_1;
  output [0:0]Res_0;

  wire [0:0]Op1_0_1;
  wire [0:0]Op2_0_1;
  wire [0:0]Op2_1_1;
  wire [0:0]util_vector_logic_0_Res;
  wire [0:0]util_vector_logic_1_Res;

  assign Op1_0_1 = Op1_0[0];
  assign Op2_0_1 = Op2_0[0];
  assign Op2_1_1 = Op2_1[0];
  assign Res_0[0] = util_vector_logic_0_Res;
  design_1_util_vector_logic_0_1 util_vector_logic_0
       (.Op1(util_vector_logic_1_Res),
        .Op2(Op2_0_1),
        .Res(util_vector_logic_0_Res));
  design_1_util_vector_logic_1_1 util_vector_logic_1
       (.Op1(Op1_0_1),
        .Op2(Op2_1_1),
        .Res(util_vector_logic_1_Res));
endmodule
