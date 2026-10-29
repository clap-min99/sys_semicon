`timescale 1ns / 1ps

module adder4(

    input [3:0] a,
    input [3:0] b,
    input cin,
    output [3:0] sum,
    output cout   

    );
    

    wire w_c0, w_c1, w_c2;

    full_adder u0_full_adder(
            .a(a[0]),
            .b(b[0]),
            .cin(cin),
            .sum(sum[0]),
            .cout(w_c0)
    );

    full_adder u1_full_adder(
            .a(a[1]),
            .b(b[1]),
            .cin(w_c0),
            .sum(sum[1]),
            .cout(w_c1)
    );

    full_adder u2_full_adder(
            .a(a[2]),
            .b(b[2]),
            .cin(w_c1),
            .sum(sum[2]),
            .cout(w_c2)
    );

    
    full_adder u3_full_adder(
            .a(a[3]),
            .b(b[3]),
            .cin(w_c2),
            .sum(sum[3]),
            .cout(cout)
    );


endmodule
