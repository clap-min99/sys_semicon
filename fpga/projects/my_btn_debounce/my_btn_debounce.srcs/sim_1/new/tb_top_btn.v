`timescale 1ns / 1ps
//==============================================================
// tb_top_btn : my_btn_debounce testbench (self-checking)
//  - 100MHz clk
//  - 시뮬레이션 시간 단축을 위해 tick 주기를 1ms -> 10us 로 100배 줄임
//    (defparam 으로 시뮬레이션에서만 변경, 소스 코드는 그대로 1ms)
//  - 모든 시간도 100배 줄여서 실제 동작과 같은 비율로 검증
//  - 버튼 누를 때/뗄 때 채터링을 넣어서
//    clean_btn이 한 번만 바뀌는지, led[2]가 한 번만 토글되는지 확인
//  - Vivado : Run Simulation 후 Tcl Console 에서  run all  (약 1.76ms)
//==============================================================
module tb_top_btn;

    reg        clk   = 1'b0;
    reg        reset = 1'b1;
    reg        btnU  = 1'b0;
    reg        btnD  = 1'b0;
    reg        sw15  = 1'b1;
    wire       clean_btn;
    wire [2:0] led;

    top_btn dut (
        .clk       (clk),
        .reset     (reset),
        .btnU      (btnU),
        .btnD      (btnD),
        .sw15      (sw15),
        .clean_btn (clean_btn),
        .led       (led)
    );

    // tick 1ms(1kHz) -> 10us(100kHz) : 시뮬레이션 전용
    defparam dut.U_TICK.TICK_HZ = 100_000;

    always #5 clk = ~clk;   // 100MHz

    //----------------------------------------------------------
    // edge counters
    //----------------------------------------------------------
    integer raw_edges   = 0;   // mux 출력(btn)의 상승 에지 수 (채터링 포함)
    integer clean_edges = 0;   // clean_btn 상승 에지 수
    integer err_cnt     = 0;

    always @(posedge dut.w_btn) raw_edges   = raw_edges + 1;
    always @(posedge clean_btn) clean_edges = clean_edges + 1;

    //----------------------------------------------------------
    // 채터링 패턴 (고정 패턴)
    //----------------------------------------------------------
    task set_btn(input sel_u, input val);
        begin
            if (sel_u) btnU = val;
            else       btnD = val;
        end
    endtask

    // 누를 때: 0/1 이 반복된 뒤 1로 안정 (총 19us = tick 1.9개)
    task bounce_press(input sel_u);
        begin
            set_btn(sel_u, 1); #2_500;
            set_btn(sel_u, 0); #2_000;
            set_btn(sel_u, 1); #4_000;
            set_btn(sel_u, 0); #4_500;
            set_btn(sel_u, 1); #3_500;
            set_btn(sel_u, 0); #2_500;
            set_btn(sel_u, 1);               // stable high
        end
    endtask

    // 뗄 때: 1/0 이 반복된 뒤 0으로 안정 (총 18us)
    task bounce_release(input sel_u);
        begin
            set_btn(sel_u, 0); #2_000;
            set_btn(sel_u, 1); #3_000;
            set_btn(sel_u, 0); #3_000;
            set_btn(sel_u, 1); #4_500;
            set_btn(sel_u, 0); #3_000;
            set_btn(sel_u, 1); #2_500;
            set_btn(sel_u, 0);               // stable low
        end
    endtask

    //----------------------------------------------------------
    // press : 채터링 -> 151us 유지 -> 채터링 -> 152us 대기 -> 검사
    //----------------------------------------------------------
    task press(input sel_u, input exp_led2, input integer exp_clean, input [8*48-1:0] name);
        integer raw0, clean0;
        begin
            raw0   = raw_edges;
            clean0 = clean_edges;

            bounce_press(sel_u);
            #151_000;                        // 151us hold
            bounce_release(sel_u);
            #152_000;                        // 152us release (한 CASE = 340us)

            $display("[%0t ns] %0s", $time, name);
            $display("    sw15=%b  raw btn edges=%0d  clean_btn edges=%0d  led[2]=%b (expect %b)",
                     sw15, raw_edges - raw0, clean_edges - clean0, led[2], exp_led2);

            if ((led[2] !== exp_led2) || ((clean_edges - clean0) != exp_clean)) begin
                $display("    --> FAIL");
                err_cnt = err_cnt + 1;
            end else
                $display("    --> PASS");
        end
    endtask

    //----------------------------------------------------------
    // scenario
    //----------------------------------------------------------
    initial begin
        $display("==== tb_top_btn start ====");
        #1_000;  reset = 1'b0;               // 1us reset
        #23_000;                             // 23us idle

        sw15 = 1'b1;
        press(1, 1'b1, 1, "CASE1 sw15=UP,   btnU press -> led2 ON ");
        press(1, 1'b0, 1, "CASE2 sw15=UP,   btnU press -> led2 OFF");
        press(0, 1'b0, 0, "CASE3 sw15=UP,   btnD press -> ignored ");

        sw15 = 1'b0;
        press(0, 1'b1, 1, "CASE4 sw15=DOWN, btnD press -> led2 ON ");
        press(1, 1'b1, 0, "CASE5 sw15=DOWN, btnU press -> ignored ");

        // CASE6 : reset
        #10_000;
        reset = 1'b1; #1_000; reset = 1'b0;
        #10;
        $display("[%0t ns] CASE6 reset -> led2=%b clean_btn=%b (expect 0 0)", $time, led[2], clean_btn);
        if (led[2] !== 1'b0 || clean_btn !== 1'b0) begin
            $display("    --> FAIL"); err_cnt = err_cnt + 1;
        end else
            $display("    --> PASS");

        #20_000;
        if (err_cnt == 0) $display("==== ALL TESTS PASSED ====");
        else              $display("==== %0d TEST(S) FAILED ====", err_cnt);
        $finish;
    end

endmodule