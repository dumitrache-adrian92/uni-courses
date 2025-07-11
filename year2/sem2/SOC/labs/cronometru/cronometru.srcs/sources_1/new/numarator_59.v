`timescale 1ns / 1ps

module numarator_59(clk_out_led, reset, pauza,
                    valoare_bin, carry_out);
    input clk_out_led, reset, pauza;
    output reg [5:0] valoare_bin;
    output reg carry_out;
    
    always @(posedge clk_out_led)
        if (reset)
            begin 
                valoare_bin = 0;
                carry_out = 0;
            end
        else if (!pauza)
            begin
                valoare_bin = valoare_bin + 1;
                                
                if (valoare_bin > 59)
                    begin 
                        carry_out = 1;
                        valoare_bin = 0;
                    end
            end
endmodule
