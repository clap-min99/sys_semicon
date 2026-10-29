
`timescale 1ns / 1ps

module moore_fsm(
    input clk,
    input reset,
    input en,
    input x,
    output reg y
);

    localparam [1:0]
        S0 = 2'b00,
        S1 = 2'b01,
        S2 = 2'b10,
        S3 = 2'b11;

    reg [1:0] r_curr_state, r_next_state;

    // 1. 현재 상태 저장
    always @(posedge clk or posedge reset) begin
        if (reset)
            r_curr_state <= S0;
        else if (en)
            r_curr_state <= r_next_state;
    end

    // 2. 다음 상태 결정
    always @(*) begin
        r_next_state = r_curr_state;

        case (r_curr_state)
            S0: begin
                if (x)
                    r_next_state = S1;
                else
                    r_next_state = S0;
            end

            S1: begin
                if (x)
                    r_next_state = S1;
                else
                    r_next_state = S2;
            end

            S2: begin
                if (x)
                    r_next_state = S3;
                else
                    r_next_state = S0;
            end

            S3: begin
                if (x)
                    r_next_state = S1;
                else
                    r_next_state = S2;
            end

            default:
                r_next_state = S0;
        endcase
    end

    // 3. Moore 출력
    // 현재 상태가 S3이면 y = 1
    always @(*) begin
        if (r_curr_state == S3)
            y = 1'b1;
        else
            y = 1'b0;
    end

endmodule
