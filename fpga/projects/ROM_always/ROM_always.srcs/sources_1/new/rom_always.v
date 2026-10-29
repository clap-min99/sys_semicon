`timescale 1ns / 1ps

 module rom_always(
    input wire [3:0] addr,
    output reg [7:0] dataout
    );

always @(*) begin
    case (addr)
        4'h0: dataout = 8'h23;
        4'h1: dataout = 8'hf3;
        4'h2: dataout = 8'ha7;
        4'h3: dataout = 8'h04;
        4'he: dataout = 8'h30;
        4'hf: dataout = 8'hd5;
        default: dataout = 8'h00;
    endcase
end
endmodule
