`timescale 1ns / 1ps

module tb_gates();
    // reg i_a;    // r_a 라는 변수는 1bit짜리 저장 메모리
    // reg i_b;    
    reg [1:0] i_a;
    wire [5:0] o_led;    // 신호선이 0~5까지 6가닥. led[0] ~ led[5]

    // port 지정: name port mapping
    gates u_gates(          // u_getes 라는 이름으로 인스턴스를 생성.
        .a(i_a),       
        .led(o_led)    // 신호선이 0~5까지 6가닥. led[0] ~ led[5]
    );


        // a b
        // 0 0
        // 0 1
        // 1 0
        // 1 1
        initial begin
            #00 i_a[0]=1'b0; i_a[1]=1'b0;
            #20 i_a[0]=1'b0; i_a[1]=1'b1;
            #20 i_a[0]=1'b1; i_a[1]=1'b0;
            #20 i_a[0]=1'b1; i_a[1]=1'b1; 
            #20 $stop;
        end

endmodule
