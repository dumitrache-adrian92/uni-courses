`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/14/2023 02:29:11 PM
// Design Name: 
// Module Name: sumator
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
module fullAdder(sum, cout, a, b);
    input [3:0] a, b;
    output [3:0] sum;
    output cout;
    
    assign {cout, sum} = a + b;
endmodule