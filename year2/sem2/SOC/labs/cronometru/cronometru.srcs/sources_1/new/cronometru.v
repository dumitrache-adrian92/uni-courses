module cronometru(input reset, pause, clk_in,
    output [7:0] An,
    output [6:0] Seg,
    output DP, clk_out_led
    );
    
    wire clk_out_seg;
    wire [5:0] valoarea_bin, valoare_bin_2;
    wire carry_out;
    wire carry_out_2;
    wire [3:0] bcd0a;
    wire [3:0] bcd1a;
    wire [3:0] bcd0b;
    wire [3:0] bcd1b;
    
    numarator_59 num_sec(clk_out_led, reset, pause, valoarea_bin, carry_out);
    numarator_59 num_min(carry_out, reset, pause, valoare_bin_2, carry_out_2);
    
    divizor_de_ceas ceas(clk_in, reset, clk_out_led, clk_out_seg);
    //assign clk_out_led = clk_in;
    //assign clk_out_seg = clk_in;
    
    bin2bcd sec_bin(valoarea_bin, bcd0a, bcd1a);
    bin2bcd min_bin(valoare_bin_2, bcd0b, bcd1b);
    afisare_7seg afis(clk_out_seg, reset, bcd0b, bcd1b, bcd0a, bcd1a, An, Seg, DP);
endmodule
