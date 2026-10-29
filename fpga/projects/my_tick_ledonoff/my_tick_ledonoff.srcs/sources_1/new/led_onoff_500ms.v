`timescale 1ns / 1ps


module led_onoff_500ms(
    input clk,
    input reset,
    input tick_1ms,
    output reg led
    );

    reg [8:0] r_count = 0;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            r_count <= 0;
            led <= 0;
        end
        else if (tick_1ms) begin
            // 500ms 마다 led 점멸
            if(r_count == 499) begin
                r_count <= 0;
                led <= ~led;
            end
            else begin
                r_count <= r_count +1;
            end
        end
        
    end

endmodule
