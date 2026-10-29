
`timescale 1ns / 1ps

module top_fsm_101_basys3(
    input clk,           // W5 : 100MHz
    input reset,         // R2 : SW0
    input btnU,          // T18: BTNU = 1
    input btnD,          // U17: BTND = 0
    output reg led,      // U16: LD0 Mealy
    output reg led_moore // E19: LD1 Moore
);

    wire step_u;
    wire step_d;

    wire step;
    wire x;

    wire mealy_y;
    wire moore_y;

    // BTNU: 1 입력 버튼
    button_step u_btnU(
        .clk(clk),
        .reset(reset),
        .btn(btnU),
        .step(step_u)
    );

    // BTND: 0 입력 버튼
    button_step u_btnD(
        .clk(clk),
        .reset(reset),
        .btn(btnD),
        .step(step_d)
    );

    // 버튼 두 개를 동시에 누르면 입력 무시
    assign step = step_u ^ step_d;

    // BTNU = 1, BTND = 0
    assign x = step_u & ~step_d;

    // Mealy FSM
    mealy_fsm u_mealy(
        .clk(clk),
        .reset(reset),
        .en(step),
        .x(x),
        .y(mealy_y)
    );

    // Moore FSM
    moore_fsm u_moore(
        .clk(clk),
        .reset(reset),
        .en(step),
        .x(x),
        .y(moore_y)
    );

    // 버튼 입력 시 출력을 LED에 저장
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            led <= 0;
            led_moore <= 0;
        end
        else if (step) begin
            led <= mealy_y;
            led_moore <= moore_y;
        end
    end

endmodule
