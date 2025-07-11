`timescale 1ns / 1ps

module divizor_de_ceas(input clk_in, input reset,
                       output clk_out_led, output clk_out_seg);
    reg[32:0] counter;
    
    always @(posedge clk_in) 
        if (reset)
            counter = 0;
        else
            counter <= counter + 1;


        assign clk_out_led = counter[26];
        assign clk_out_seg = counter[17];
endmodule
