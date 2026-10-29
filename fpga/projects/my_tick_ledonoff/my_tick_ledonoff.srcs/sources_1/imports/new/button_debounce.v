`timescale 1ns / 1ps

module button_debounce(
        input clk,
        input reset,
        input btnC,
        output clean_btn
    );

    wire w_clk;
    wire w_Q1;
    wire w_Q2, w_Q2_bar;

    clock_80Hz u_clock_80Hz(
        .clk(clk),          // 100MHz
        .reset(reset),      // reset
        .oclk(w_clk)             // 80MHz
    );      

    D_FF u1_D_FF(
        .clk(w_clk),
        .reset(reset),
        .D(btnC),
        .Q(w_Q1)
    );
    
    D_FF u2_D_FF(
        .clk(w_clk),
        .reset(reset),
        .D(w_Q1),
        .Q(w_Q2)
    );

    assign w_Q2_bar = ~w_Q2;
    assign clean_btn = w_Q1 & w_Q2_bar;
endmodule
