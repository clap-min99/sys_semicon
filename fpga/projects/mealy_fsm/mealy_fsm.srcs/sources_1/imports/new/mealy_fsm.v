
`timescale 1ns / 1ps

module mealy_fsm(
    input clk,
    input reset,
    input en,
    input x,
    output reg y
);

    localparam [1:0]
        S0 = 2'b00,
        S1 = 2'b01,
        S2 = 2'b10;

    reg [1:0] r_curr_state, r_next_state;

    // 현재 상태 저장
    always @(posedge clk or posedge reset) begin
        if (reset)
            r_curr_state <= S0;
        else if (en)
            r_curr_state <= r_next_state;
    end

    // 다음 상태 및 출력 결정
    always @(*) begin
        r_next_state = r_curr_state;
        y = 1'b0;

        case (r_curr_state)
            S0: begin
                if (x)
                    r_next_state = S1;
            end

            S1: begin
                if (!x)
                    r_next_state = S2;
            end

            S2: begin
                if (x) begin
                    y = 1'b1;
                    r_next_state = S1;
                end
                else
                    r_next_state = S0;
            end

            default:
                r_next_state = S0;
        endcase
    end

endmodule
