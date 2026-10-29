`timescale 1ns / 1ps
// clean_btn의 상승 에지(누르는 순간)마다 led 반전
module led_toggle (
    input  wire btn,        // btn_debounce의 clean_btn
    input  wire reset,
    output reg  led
);
    always @(posedge btn or posedge reset) begin
        if (reset)
            led <= 1'b0;
        else
            led <= ~led;
    end
endmodule
