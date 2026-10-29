`timescale 1ns / 1ps

module gates(

    input wire a,
    input b,
    output [5:0] led    // 신호선이 0~5까지 6가닥. led[0] ~ led[5]

    );

    assign led[0] = a & b;     // AND
    assign led[1] = a | b;     // OR
    assign led[2] = ~(a & b);  // NAND
    assign led[3] = ~(a | b);  // NOR
    assign led[4] = a ^ b;     // XOR
    assign led[5] = ~a;        // NOT

endmodule



// module gates(

//     input a,
//     input b,
//     output ld0,
//     output ld1,
//     output ld2,
//     output ld3,
//     output ld4,
//     output ld5

//     );

//     assign ld0 = a & b;     // AND
//     assign ld1 = a | b;     // OR
//     assign ld2 = ~(a & b);  // NAND
//     assign ld3 = ~(a | b);  // NOR
//     assign ld4 = a ^ b;     // XOR
//     assign ld5 = ~a;        // NOT

// endmodule
