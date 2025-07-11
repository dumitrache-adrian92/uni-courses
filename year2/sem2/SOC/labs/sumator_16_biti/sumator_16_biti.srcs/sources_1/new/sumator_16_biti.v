`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/09/2023 03:17:18 PM
// Design Name: 
// Module Name: sumator_16_biti
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sumator_16_biti(
        input [15:0] a, b,
        input cin,
        output [15:0] result,
        output cout
    );
    
    wire carry1, carry2, carry3, carry4;
    wire G0,G1,G2,G3,P0,P1,P2,P3;
    sumator_4_biti sumator1(a[3:0], b[3:0], cin, P0, G0, result[3:0]);
    assign carry1 = G0 | P0 & cin;
    sumator_4_biti sumator2(a[7:4], b[7:4], carry1, P1, G1, result[7:4]);
    assign carry2 = G1 | P1 & G0 | P1 & P0 & cin;
    sumator_4_biti sumator3(a[11:8], b[11:8], carry2, P2, G2, result[11:8]);
    assign carry3 = G2 | P2 & G1 | P2 & P1 & G0 | P2 & P1 & P0 & cin;
    sumator_4_biti sumator4(a[15:12], b[15:12], carry3, P3, G3, result[15:12]);
    assign cout = G3 | P3 & G2 | P3 & P2 & G1 | P3 & P2 & P1 & G0 | P3 & P2 & P1 & P0 & cin;
endmodule
