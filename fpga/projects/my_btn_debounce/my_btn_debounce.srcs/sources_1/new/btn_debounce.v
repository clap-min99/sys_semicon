`timescale 1ns / 1ps
// 1ms tick을 클럭으로 받아 버튼을 샘플링
// 8번(8ms) 연속 1이면 clean_btn = 1, 8번 연속 0이면 clean_btn = 0
module btn_debounce (
    input  wire clk,        // tick_generator의 1ms tick이 들어옴
    input  wire reset,
    input  wire btn,
    output reg  clean_btn
);
    reg [7:0] r_shift;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            r_shift   <= 8'b0;
            clean_btn <= 1'b0;
        end else begin
            r_shift <= {r_shift[6:0], btn};       // 샘플을 시프트 레지스터에 밀어 넣음

            if (&r_shift)                          // 전부 1
                clean_btn <= 1'b1;
            else if (~|r_shift)                    // 전부 0
                clean_btn <= 1'b0;
            // 그 외(섞여 있음 = 채터링 중)에는 이전 값 유지
        end
    end
endmodule
