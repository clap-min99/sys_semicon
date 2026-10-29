set root [file normalize [file join [file dirname [info script]] ..]]
create_project -in_memory -part xc7a35tcpg236-1
read_verilog [glob $root/pwm_motor.srcs/sources_1/imports/sources_1/imports/new/*.v]
read_verilog $root/pwm_motor.srcs/sources_1/imports/sources_1/imports/Downloads/button_debounce_10ms.v
read_verilog $root/pwm_motor.srcs/sources_1/imports/sources_1/new/pwm_duty_control.v
read_xdc $root/pwm_motor.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc
synth_design -top top
report_drc -file $root/tests/synthesis_drc.rpt
report_io -file $root/tests/synthesis_io.rpt
