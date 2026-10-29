`timescale 1ns / 1ps

module tick_generator(
    input clk,
    input reset,
    output reg tick_1ms
    );

    reg [16:0] r_counter = 0;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            r_counter <= 0;
            tick_1ms <= 0;
        end
        else begin
            if (r_counter == 99999) begin
                r_counter <= 0;
                tick_1ms <= 1;
            end
            else begin
                r_counter <= r_counter + 1;
                tick_1ms <= 0;
            end
        end
    end

endmodule
