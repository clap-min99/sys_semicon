`timescale 1ns / 1ps
module top_btn (
    input  wire       clk,        // 100MHz
    input  wire       reset,      // btnC
    input  wire       btnU,
    input  wire       btnD,
    input  wire       sw15,       // sel
    output wire       clean_btn,  // JA3 (Pmod) -> 오실로스코프 확인용
    output wire [2:0] led
);
    wire w_tick;
    wire w_btn;
    wire w_clean_btn;
    wire w_led_toggle;

    // 1ms tick 생성
    tick_generator U_TICK (
        .clk   (clk),
        .reset (reset),
        .tick  (w_tick)
    );

    // sw15로 btnU / btnD 선택
    btn_mux U_MUX (
        .sel  (sw15),
        .btnU (btnU),
        .btnD (btnD),
        .btn  (w_btn)
    );

    // 디바운스 (tick을 clk 포트로)
    btn_debounce U_DEBOUNCE (
        .clk       (w_tick),
        .reset     (reset),
        .btn       (w_btn),
        .clean_btn (w_clean_btn)
    );

    // 누를 때마다 LED 토글
    led_toggle U_TOGGLE (
        .btn   (w_clean_btn),
        .reset (reset),
        .led   (w_led_toggle)
    );

    assign clean_btn = w_clean_btn;
    assign led[0]    = w_clean_btn;    // 누르고 있는 동안 ON
    assign led[1]    = 1'b0;           // 사용 안 함
    assign led[2]    = w_led_toggle;   // 누를 때마다 ON/OFF
endmodule
