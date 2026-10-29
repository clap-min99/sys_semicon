`timescale 1ns / 1ps



module top(
    input clk,
    input reset,
    input [2:0] btn,
    input [1:0] sw,
    output [7:0] seg,
    output [3:0] an,
    output pwm_out,
    output pwm_scope,
    output pwm_out_led,
    output [1:0] in1_in2
    );
    
    wire [2:0] w_clean_btn;
    wire [13:0] w_seg_data;
    wire w_tick;
    wire [3:0] w_duty_cycle;

    btn_debouncer u_btn_debouncer(
        .clk(clk),
        .reset(reset),
        .noisy_btn(btn),
        .clean_btn(w_clean_btn)
    );

    pwm_duty_control u_pwm_duty_control(
    .clk(clk),
    .reset(reset),
    .clean_btn(w_clean_btn),
    .duty_cycle(w_duty_cycle),
    .pwm_out(pwm_out),
    .pwm_out_led(pwm_out_led)
    );

    tick_generator u_tick_generator(
        .clk(clk),
        .reset(reset),
        .tick(w_tick)
    );

    fnd_controller u_fnd_controller(
        .clk(clk),
        .reset(reset),
        .tick(w_tick),
        .in_data(w_seg_data),
        .motor_direction(sw),
        .an(an),
        .seg(seg)
    );

    assign in1_in2 = sw;
    assign w_seg_data = {10'b0, w_duty_cycle} * 14'd10;
    assign pwm_scope = pwm_out;

endmodule
