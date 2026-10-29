`timescale 1ns / 1ps

module tb_adder7();

    reg  [6:0] a;
    reg  [6:0] b;
    reg  cin;

    wire [6:0] sum;
    wire cout;


    adder7 u_adder7(
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .cout(cout)
    );


    initial begin

        // a + b + cin

        a = 7'b0000000; b = 7'b0000000; cin = 1'b0;
        #20;

        a = 7'b0000001; b = 7'b0000001; cin = 1'b0;
        #20;

        a = 7'b0000011; b = 7'b0000101; cin = 1'b0;
        #20;

        a = 7'b0000111; b = 7'b0001001; cin = 1'b0;
        #20;

        a = 7'b0111111; b = 7'b0000001; cin = 1'b0;
        #20;

        a = 7'b1111111; b = 7'b0000001; cin = 1'b0;
        #20;

        a = 7'b1111111; b = 7'b1111111; cin = 1'b1;
        #20;

        $stop;
    end

endmodule