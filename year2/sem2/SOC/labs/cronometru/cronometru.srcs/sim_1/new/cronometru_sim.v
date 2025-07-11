`timescale 1ns / 1ps

module cronometru_sim();
    reg clk, reset, pauza;
    
    wire [7:0] AN;
    wire [6:0] Seg;
    wire DP, clk_out_led;
    
    cronometru name(reset, pauza, clk, AN, Seg, DP, clk_out_led);
    
    always #10 clk = ~clk;
    
    initial begin
        reset = 0; clk = 0; pauza = 0;
        #20;
        reset = 1;
        #20; 
        reset = 0;
        #300 pauza = 1;
        #40 pauza = 0;
        #20;
        reset = 1;
        #20; 
        reset = 0;
    end
endmodule
