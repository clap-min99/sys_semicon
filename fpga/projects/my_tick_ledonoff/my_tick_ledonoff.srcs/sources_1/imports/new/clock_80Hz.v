`timescale 1ns / 1ps

module clock_80Hz(
    input clk,
    input reset,
    output reg oclk
    );

    // 10ns의 clk이 상승엣지이거나 reset 신호가 오면 항상 수행
    
    reg [$clog2(1250000) - 1:0] r_counter=0;
    always @(posedge clk, posedge reset) begin
        if (reset) begin
            oclk <= 0;
            r_counter <= 0;
        end else begin
            if (r_counter == (1_250_000/2)-1) begin
                r_counter <= 0;
                oclk <= ~oclk;
            end else begin
                    r_counter <= r_counter + 1;
                end
            end
        end
endmodule
