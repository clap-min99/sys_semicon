open_vcd tests/motor_waveform.vcd
log_vcd /tb_motor/clk /tb_motor/btn /tb_motor/duty /tb_motor/pwm /tb_motor/led
run all
close_vcd
quit
