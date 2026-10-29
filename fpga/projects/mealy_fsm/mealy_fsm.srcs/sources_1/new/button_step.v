`timescale 1ns / 1ps

module button_step #(parameter integer COUNT_MAX = 999_999)(
    input clk, input reset, input btn, output reg step
);
    reg sync1, sync2;
    reg stable;
    reg [19:0] count;
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            sync1 <= 0;
            sync2 <= 0;
            stable <= 0;
            count <= 0;
            step <= 0;
        end else begin
            sync1 <= btn;
            sync2 <= sync1;
            step <= 0;
            if (sync2 == stable) count <= 0;
            else if (count == COUNT_MAX) begin
                stable <= sync2;
                count <= 0;
                if (sync2) step <= 1;
            end else count <= count + 1'b1;
        end
    end
endmodule
