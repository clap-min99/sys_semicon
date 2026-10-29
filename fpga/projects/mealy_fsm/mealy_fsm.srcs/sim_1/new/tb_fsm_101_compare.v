
`timescale 1ns / 1ps

module tb_fsm_101_compare();

    reg clk = 0;
    reg reset = 1;
    reg en = 0;
    reg x = 0;

    wire moore_y, mealy_y;
    reg r_error = 1'b0;

    // Moore FSM
    moore_fsm u_moore_fsm (
        .clk(clk),
        .reset(reset),
        .en(en),
        .x(x),
        .y(moore_y)
    );

    // Mealy FSM
    mealy_fsm u_mealy_fsm (
        .clk(clk),
        .reset(reset),
        .en(en),
        .x(x),
        .y(mealy_y)
    );

    // 100MHz clock
    always #5 clk = ~clk;

    task send_data;
        input a, expect_moore, expect_mealy;
        begin
            // 이전 상승엣지 이후 입력 설정
            x = a;
            en = 1'b1;
            #1;

            $display("t=%0t x=%b Moore=%b Mealy=%b",
                     $time, x, moore_y, mealy_y);

            if (moore_y !== expect_moore ||
                mealy_y !== expect_mealy) begin
                r_error = 1'b1;
                $display("FAIL: expected Moore=%b Mealy=%b",
                         expect_moore, expect_mealy);
            end

            // 다음 상승엣지에서 상태 전이
            @(posedge clk);
            #1;

            en = 1'b0;
        end
    endtask

    initial begin
        #202 reset = 0;

        send_data(1,0,0); // t0
        send_data(0,0,0); // t1
        send_data(1,0,1); // t2
        send_data(0,1,0); // t3
        send_data(1,0,1); // t4
        send_data(1,1,0); // t5
        send_data(0,0,0); // t6
        send_data(1,0,1); // t7
        send_data(0,1,0); // t8

        if (!r_error)
            $display("PASS: Moore/Mealy 101 comparison");
        else
            $display("FAIL: Moore/Mealy 101 comparison");

        #10 $finish;
    end

endmodule
