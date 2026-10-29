`timescale 1ns / 1ps

// moore fsm: 입력 x에서 101 시퀀스(중첩허용)
//             출력 y(s3상태로 왔을 때 y가 1로 됨)
module moore_fsm_101(
    input clk,
    input reset,
    input x,
    output y
    );

    //상태인코딩 (S0: 대기 , S1: 1검출, S2: 10검출, S3: 101검출 )
    localparam [1:0] S0 = 2'b00,    // IDLE
                     S1 = 2'b01,    // 1검출
                     S2 = 2'b10,    // 10검출
                     S3 = 2'b11;    // 101검출

    reg [1:0] curr_state, next_state;

    // 1. curr state 상태 register(순차회로)
    always @(posedge clk, posedge reset) begin
        if (reset) curr_state <= S0;
        else curr_state <= next_state;
    end 

    // 2. 다음 상태 로직 (조합회로)
    always @(*) begin
        case (curr_state)
            S0: next_state = x ? S1 : S0;
            S1: next_state = x ? S1 : S2;
            S2: next_state = x ? S3 : S0;
            S3: next_state = x ? S1 : S2;   // 중첩 허용
            default: next_state = S0;       // 래치 방지
        endcase
    end

    // 3. 출력 로직
    assign y = (curr_state == S3);
endmodule   
