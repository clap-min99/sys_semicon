`timescale 1ns / 1ps

module tb_adder4();

    reg  [3:0] a;
    reg  [3:0] b;
    reg   cin;

    wire [3:0] sum;
    wire  cout;

    adder4 u_adder4(
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .cout(cout)
    );

    initial begin
        a = 4'b0000; b = 4'b0000; cin = 1'b0;
        #20;

        a = 4'b0001; b = 4'b0001; cin = 1'b0;
        #20;

        a = 4'b0011; b = 4'b0101; cin = 1'b0;
        #20;

        a = 4'b0111; b = 4'b1001; cin = 1'b0;
        #20;

        a = 4'b1111; b = 4'b0001; cin = 1'b0;
        #20;

        a = 4'b1111; b = 4'b1111; cin = 1'b1;
        #20;

        $stop;
    end

endmodule