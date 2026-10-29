`timescale 1ns / 1ps
// 100MHz clk를 분주하여 1ms마다 1클럭 폭의 tick 펄스 출력
module tick_generator #(
    parameter CLK_FREQ = 100_000_000,   // 입력 클럭 100MHz
    parameter TICK_HZ  = 1_000          // 1kHz = 1ms
)(
    input  wire clk,
    input  wire reset,
    output reg  tick
);
    localparam integer COUNT_MAX = CLK_FREQ / TICK_HZ;   // 100,000

    reg [$clog2(COUNT_MAX)-1:0] r_count;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            r_count <= 0;
            tick    <= 1'b0;
        end else if (r_count == COUNT_MAX - 1) begin
            r_count <= 0;
            tick    <= 1'b1;     // 1ms마다 1클럭 동안만 1
        end else begin
            r_count <= r_count + 1;
            tick    <= 1'b0;
        end
    end
endmodule
