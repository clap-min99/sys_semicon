`timescale 1ns / 1ps
// sel(sw15) = 1(UP)   -> btnU 선택
// sel(sw15) = 0(DOWN) -> btnD 선택
module btn_mux (
    input  wire sel,
    input  wire btnU,
    input  wire btnD,
    output wire btn
);
    assign btn = sel ? btnU : btnD;
endmodule
