`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/09/2023 03:21:37 PM
// Design Name: 
// Module Name: sumator_16_biti_sim
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


module sumator_16_biti_sim(

    );
    
    reg[15:0] a, b;
    reg cin;
    wire[15:0] result;
    wire cout;
    
    sumator_16_biti nume(a, b, cin, result, cout);
    
    initial begin 
        a=0; b=0; cin=0;
        #50
        a=2000;
        b=3000;
        #50
        a = 100;
        b = 200;
        #50
        a = 65535;
        b = 1;
    end
endmodule
