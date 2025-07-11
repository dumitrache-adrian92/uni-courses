`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/09/2023 02:59:26 PM
// Design Name: 
// Module Name: sumator_4_biti_sim
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


module sumator_4_biti_sim();
    reg[3:0] a, b;
    reg c;
    wire[3:0] rez;
    wire P, G;
    sumator_4_biti nume(a, b, c, P, G, rez);
    
    initial begin 
        a=0; b=0; c=0;
        #50
        a=4;
        b=5;
    end
endmodule
