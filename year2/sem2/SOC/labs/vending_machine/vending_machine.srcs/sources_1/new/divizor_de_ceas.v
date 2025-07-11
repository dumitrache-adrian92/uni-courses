`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/02/2023 02:14:06 PM
// Design Name: 
// Module Name: divizor_de_ceas
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


`timescale 1ns / 1ps

module divizor_de_ceas(input clk_in, input reset,
                       output clk_out);
    reg[32:0] counter;
    
    always @(posedge clk_in) 
        if (reset)
            counter = 0;
        else
            counter <= counter + 1;


        assign clk_out = counter[26];
endmodule

