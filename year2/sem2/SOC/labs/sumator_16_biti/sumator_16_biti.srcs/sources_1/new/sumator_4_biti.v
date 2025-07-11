`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/09/2023 02:32:12 PM
// Design Name: 
// Module Name: sumator_4_biti
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


module sumator_4_biti(input[3:0] a, b,
                      input cin,
                      output P, G,
                      output[3:0] result);
                      
    wire [3:0] p, g, c;
    assign g = a & b;
    assign p = a | b;
    assign c[0] = g[0] | p[0] & cin;
    assign c[1] = g[1] | p[1] & g[0] | p[1] & p[0] & cin;
    assign c[2] = g[2] | p[2] & g[1] | p[2] & p[1] & g[0] | p[2] & p[1] & p[0] & cin;
    
    assign result[0] = a[0] ^ b[0] ^ cin;
    assign result[1] = a[1] ^ b[1] ^ c[0];
    assign result[2] = a[2] ^ b[2] ^ c[1];
    assign result[3] = a[3] ^ b[3] ^ c[2];
    
    assign P = p[3] & p[2] & p[1] & p[0];
    assign G = g[3] | p[3] & g[2] | p[3] & p[2] & g[1] | p[3] & p[2] & p[1] & g[0];
    
endmodule
