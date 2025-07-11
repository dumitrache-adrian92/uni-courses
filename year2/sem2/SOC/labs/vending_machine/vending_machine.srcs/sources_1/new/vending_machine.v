`timescale 1ns / 1ps

module vending_machine(reset, clk, IN1, IN2, IN5,
                        SUC, OUT1, OUT2, OUT_LED);
    reg [2:0] state, next_state;
    input reset, clk, IN1, IN2, IN5;
    output reg SUC, OUT1, OUT2, OUT_LED;
    reg next_SUC, next_OUT1, next_OUT2;
    
    wire clk_out_sec;
    
    divizor_de_ceas ceas(clk, reset, clk_out_sec);
    
    always @(posedge clk_out_sec)
    begin
        if (reset)
        begin
            state <= 3'b000;
            SUC <= 0;
            OUT1 <= 0;
            OUT2 <= 0;
            OUT_LED <=0;
        end
        else
            state <= next_state;
            SUC <= next_SUC;
            OUT1 <= next_OUT1;
            OUT2 <= next_OUT2;
            OUT_LED <= ~OUT_LED;
    end
    
    always @(state or IN1 or IN2 or IN5)
        casez ({state, IN1, IN2, IN5})
     
        6'b000100:
        begin
                next_state = 3'b001;
                next_SUC = 0;
                next_OUT1 = 0;
                next_OUT2 = 0;
        end
        
        6'b000010:
        begin
                next_state = 3'b010;
                next_SUC = 0;
                next_OUT1 = 0;
                next_OUT2 = 0;
        end
        
        6'b000001:
        begin
                next_state = 3'b000;
                next_SUC = 1;
                next_OUT1 = 0;
                next_OUT2 = 1;
        end
        
        6'b001100:
        begin
                next_state = 3'b010;
                next_SUC = 0;
                next_OUT1 = 0;
                next_OUT2 = 0;
        end
        
        6'b001010:
        begin
                next_state = 3'b000;
                next_SUC = 1;
                next_OUT1 = 0;
                next_OUT2 = 0;
        end
        
        6'b001001:
        begin
                next_state = 3'b000;
                next_SUC = 1;
                next_OUT1 = 1;
                next_OUT2 = 1;
        end
        
        6'b010100:
        begin
                next_state = 3'b000;
                next_SUC = 1;
                next_OUT1 = 0;
                next_OUT2 = 0;
        end
        
        6'b010010:
        begin
                next_state = 3'b000;
                next_SUC = 1;
                next_OUT1 = 1;
                next_OUT2 = 0;
        end
        
        6'b010001:
        begin
                next_state = 3'b011;
                next_SUC = 1;
                next_OUT1 = 0;
                next_OUT2 = 1;
        end
        
        6'b011???:
        begin
                next_state = 3'b000;
                next_SUC = 0;
                next_OUT1 = 0;
                next_OUT2 = 1;
        end
        default:
        begin
            next_state = state;
            next_SUC = 0;
            next_OUT1 = 0;
            next_OUT2 = 0;
        end
        
        endcase
endmodule
