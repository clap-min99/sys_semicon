`timescale 1ns / 1ps


module top_btn_debounce(
    input clk,
    input reset,
    input btn,
    output led
    );

    wire w_clean_btn;

    debouncer u_button_debounce(
        .clk(clk),
        .reset(reset),
        .noisy_btn(btn),
        .clean_btn(w_clean_btn)
    );

    led_toggle u_led_toggle(
        .clean_btn(w_clean_btn),
        .led(led)
    );

endmodule
