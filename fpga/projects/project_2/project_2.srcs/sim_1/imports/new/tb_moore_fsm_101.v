`timescale 1ns / 1ps


module tb_mealy_fsm_101();
    
    reg clk=0;
    reg reset=1;
    reg x=0;   // 입력
    wire y;     // 출력
    
    reg r_error=1'b0;

    mealy_fsm u_mealy_fsm(
        .clk(clk),
        .reset(reset),    
        .x(x),
        .y(y)
    );

    always #5 clk = ~clk; // 100MHz clk 생성

    // 상승엣지 전에 출력 y가 변하는지를 검사하는 것(moore상태)
    // 상승엣지 후에 출력 y가 기대하는 값인지 검사(1 clock 지연)
    task send_data(input a, input expect_val);
        begin  
            x=a; #1;    // gate 동작
            @(posedge clk); x=a; #1;
            if (y !== expect_val) begin // y가 기대값이 아닌 다른 값이면 DUT에 logic error가 발생되었다
                r_error=1'b1;   // error detect flag
                $display("FAIL t=%0t x=%b y=%b expect_val=%b", $time, a, y, expect_val);
            end
        end
    endtask

    // 10101101
    initial begin
        #100 reset=1;
        #100 reset=0;
        send_data(1,0);
        send_data(0,0);
        send_data(1,1); // 101 : 다음 엣지 후 y=1(S3)
        send_data(0,0); send_data(1,1);     // 10101: 중첩 검증
        send_data(1,0); send_data(0,0); send_data(1,1); // 1101: 검출
        if (r_error == 0) $display("PASS mealy fsm_101");
        else $display("FAIL mealy fsm_101");
        $finish;
    end

endmodule
