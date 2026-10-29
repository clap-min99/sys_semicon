`timescale 1ns / 1ps


module rom_always_tb(

    );

reg [3:0] addr;
wire [7:0] dataout;

rom_always uut (
    .addr(addr),
    .dataout(dataout)
);

initial begin
    addr = 4'h0; #10;
    addr = 4'h1; #10;
    addr = 4'h2; #10;
    addr = 4'h3; #10;
    addr = 4'he; #10;
    addr = 4'hf; #10;

    $finish;
end

endmodule
