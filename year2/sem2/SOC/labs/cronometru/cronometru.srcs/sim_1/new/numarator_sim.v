`timescale 1ns / 1ps

module numarator_sim();
    reg clk, reset, pauza;
    
    wire [5:0] valoare_bin;
    wire carry;
    
    numarator_59 name(clk, reset, pauza, valoare_bin, carry);
    always #10 clk = ~clk;
    
    initial begin
        reset = 1; clk = 0; pauza = 0;
        #20 reset = 0;
        #300 pauza = 1;
        #40 pauza = 0;
    end
endmodule
