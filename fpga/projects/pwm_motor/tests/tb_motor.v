`timescale 1ns / 1ps
module tb_motor;
    reg clk = 0;
    always #5 clk = ~clk;
    reg reset = 1;
    reg tick = 0;
    reg [2:0] btn = 0;
    reg [1:0] direction = 2'b10;
    reg [13:0] data = 50;
    wire [3:0] duty, an;
    wire [7:0] seg;
    wire pwm, led;
    integer i, n, high_count;
    pwm_duty_control pwm_dut(clk, reset, btn, duty, pwm, led);
    fnd_controller #(.BLINK_CYCLES(100)) fnd_dut(
        clk, reset, tick, data, direction, an, seg);

    task press;
        input [2:0] buttons;
        begin
            @(negedge clk); btn = buttons;
            repeat (3) @(negedge clk);
            btn = 0;
            repeat (3) @(negedge clk);
        end
    endtask

    task check_pwm;
        input integer expected;
        begin
            high_count = 0;
            for (n = 0; n < 100; n = n + 1) begin
                @(negedge clk);
                if (pwm) high_count = high_count + 1;
                if (expected == 0 && pwm !== 1'b0)
                    $fatal(1, "zero duty must stay LOW");
                if (led !== pwm) $fatal(1, "LED mismatch");
            end
            if (high_count != expected * 10 || duty != expected)
                $fatal(1, "PWM mismatch duty=%0d high=%0d", duty, high_count);
            $display("PWM duty=%0d%% period=100ns high=%0dns", expected * 10, expected * 10);
        end
    endtask

    initial begin
        #1; reset = 0; #1; reset = 1;
        repeat (2) @(negedge clk);
        reset = 0;
        // Scan the decimal digits and direction immediately after reset.
        #1;
        if (an !== 4'b1110 || seg !== 8'hc0) $fatal(1, "ones digit");
        data = 51; #1;
        if (seg !== 8'hf9) $fatal(1, "data did not update without scan");
        data = 50;
        repeat (3) begin
            tick = 1; @(negedge clk); tick = 0; @(negedge clk);
        end
        if (an !== 4'b0111 || seg !== 8'h8e) $fatal(1, "forward F");
        direction = 2'b01; #1;
        if (seg !== 8'h83) $fatal(1, "reverse b");
        direction = 2'b11; #1;
        if (seg !== 8'hff) $fatal(1, "stop blank");
        direction = 2'b00; #1;
        if (seg !== 8'hff) $fatal(1, "00 blank");
        direction = 2'b10;
        // Exactly 100 clock edges per blink phase in the accelerated test.
        wait (!fnd_dut.blink_on); #1;
        if (seg !== 8'hff) $fatal(1, "blink off");
        repeat (99) @(negedge clk);
        if (fnd_dut.blink_on) $fatal(1, "blink phase too short");
        wait (fnd_dut.blink_on); #1;
        if (seg !== 8'h8e) $fatal(1, "blink on");
        check_pwm(5);
        for (i = 6; i <= 9; i = i + 1) begin press(1); check_pwm(i); end
        press(1); check_pwm(9);
        for (i = 8; i >= 0; i = i - 1) begin press(2); check_pwm(i); end
        press(2); check_pwm(0);
        @(negedge clk); btn = 1;
        repeat (50) @(negedge clk);
        if (duty != 1) $fatal(1, "held button repeated");
        btn = 0;
        reset = 1; #1;
        if (duty != 5 || an !== 4'b1110) $fatal(1, "reset");
        $display("PASS: PWM bounds, held button, direction, display updates, blink and reset");
        $finish;
    end
    initial begin #100000; $fatal(1, "timeout"); end
endmodule
