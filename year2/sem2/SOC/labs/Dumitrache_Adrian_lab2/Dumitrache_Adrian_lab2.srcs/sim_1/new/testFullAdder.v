`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/14/2023 03:16:10 PM
// Design Name: 
// Module Name: testFullAdder
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


module testFullAdder();
    reg [3:0] a, b;
    wire [3:0] sum;
    wire c;
    
    fullAdder inst(sum, c, a, b);
    
    initial begin
        a = 0; b = 0;
        #50 a = 5; b = 2;
        #50 a = 7; b = 1;
        #50 a = 15; b = 15;
    end
endmodule
