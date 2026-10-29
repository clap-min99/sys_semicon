`timescale 1ns / 1ps


module top_moore_fsm(
    input clk,
    input reset,    // 비동기 reset, active-high
    input btnC,
    output led
    );

    debouncer u_btn_debouncer(
        .clk(clk),
        .reset(reset),
        .noisy_btn(btnC),  // raw noisy button input
        .clean_btn(w_clean_btn)
    );

    moore_fsm_101 u_moore_fsm_101(
        .clk(clk),
        .reset(reset),
        .x(clean_btn),
        .y(led)
    );

    // led_toggle u_led_toggle(
    //     .clean_btn(w_clean_btn),
    //     .led()
    // );
    
endmodule
