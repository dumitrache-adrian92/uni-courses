`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/25/2023 03:04:10 PM
// Design Name: 
// Module Name: vending_machine_sim
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


module vending_machine_sim();
    reg reset, clk, IN1, IN2, IN5;
    wire SUC, OUT1, OUT2;
    
    vending_machine name(reset, clk, IN1, IN2, IN5, SUC, OUT1, OUT2);
    
    always #10 clk = ~clk;
    
    initial begin
        reset = 1; clk = 0; IN1 = 0; IN2 = 0; IN5 = 0;
        #100 reset = 0;
        #40 IN1 = 1;
        #20 IN1 = 0;
        #20 IN5 = 1;
        #20 IN5 = 0;
        #20 IN5 = 1;
        #20 IN5 = 0;
    end
endmodule
