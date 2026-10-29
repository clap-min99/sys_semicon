`timescale 1ns / 1ps

module tb_adder7();

    reg  [6:0] a;
    reg  [6:0] b;
    reg        cin;

    wire [6:0] sum;
    wire       cout;


    adder7 u_adder7(
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .cout(cout)
    );


    initial begin

        // 1 + 1 = 2
        a = 7'b0000001;
        b = 7'b0000001;
        cin = 1'b0;
        #20;

        // 3 + 5 = 8
        a = 7'b0000011;
        b = 7'b0000101;
        cin = 1'b0;
        #20;

        // 7 + 9 = 16
        a = 7'b0000111;
        b = 7'b0001001;
        cin = 1'b0;
        #20;

        // 63 + 1 = 64
        a = 7'b0111111;
        b = 7'b0000001;
        cin = 1'b0;
        #20;

        // 127 + 1 = 128
        a = 7'b1111111;
        b = 7'b0000001;
        cin = 1'b0;
        #20;

        // cin 동작 확인
        // 1 + 1 + 1 = 3
        a = 7'b0000001;
        b = 7'b0000001;
        cin = 1'b1;
        #20;

        // 최대값 확인
        // 127 + 127 + 1 = 255
        a = 7'b1111111;
        b = 7'b1111111;
        cin = 1'b1;
        #20;

        $stop;

    end

endmodule