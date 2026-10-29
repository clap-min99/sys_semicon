# 프로젝트별 코드 목록

원본: `D:\project\fpga\ai2` / 정리일: 2026-10-26

경로 구조와 코드 바이트를 보존했다. 외부 의존 파일은 external에 복사하고 복사본 XPR 참조만 조정했다.
XPR은 텍스트 저장 과정에서 줄바꿈이 바뀔 수 있으므로 매니페스트의 XPR 해시는 원본 기준이다.

| 프로젝트 | 설계 Top | 시뮬레이션 Top | 복사 파일 수 |
|---|---|---|---|
| 01.gate_test | gates | tb_gates | 4 |
| 02.adder | full_adder | tb_half_adder | 5 |
| 03.adder4 | adder4 | tb_adder4 | 8 |
| 06.dff_btn_debounce | top_btn_debounce | top_btn_debounce | 7 |
| 06_1.btn_debounce_10ms | top_btn_debounce | top_btn_debounce | 9 |
| 07.moore_fsm_101_detect | top_moore_fsm | tb_moore_fsm_101 | 7 |
| 09.up_down_counter | top | top | 7 |
| 10.pwm_control | top | top | 7 |
| 999.7bit_full_adder | adder7 | tb_adder7 | 5 |
| adder7 | adder7 | tb_adder7 | 7 |
| mealy_fsm | top_fsm_101_basys3 | tb_fsm_101_compare | 8 |
| my_btn_debounce | top_btn | tb_top_btn | 7 |
| my_tick_ledonoff | top_btn_debounce | top_btn_debounce | 9 |
| project_1 | - | - | 0 |
| project_2 | mealy_fsm | tb_mealy_fsm_101 | 4 |
| pwm_motor | top | top | 11 |
| ROM_always | rom_always | rom_always_tb | 4 |
| stopwatch | top | tb_tick_generator | 13 |

## 01.gate_test

설계 Top: `gates` / 시뮬레이션 Top: `tb_gates`

- [01.gate_test.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/01.gate_test/01.gate_test.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [01.gate_test.srcs/sim_1/new/tb_gates.v](../projects/01.gate_test/01.gate_test.srcs/sim_1/new/tb_gates.v)
- [01.gate_test.srcs/sources_1/new/gates.v](../projects/01.gate_test/01.gate_test.srcs/sources_1/new/gates.v)
- [01.gate_test.xpr](../projects/01.gate_test/01.gate_test.xpr)

## 02.adder

설계 Top: `full_adder` / 시뮬레이션 Top: `tb_half_adder`

- [02.adder.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/02.adder/02.adder.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [02.adder.srcs/sim_1/new/tb_half_adder.v](../projects/02.adder/02.adder.srcs/sim_1/new/tb_half_adder.v)
- [02.adder.srcs/sources_1/new/full_adder.v](../projects/02.adder/02.adder.srcs/sources_1/new/full_adder.v)
- [02.adder.srcs/sources_1/new/half_adder.v](../projects/02.adder/02.adder.srcs/sources_1/new/half_adder.v)
- [02.adder.xpr](../projects/02.adder/02.adder.xpr)

## 03.adder4

설계 Top: `adder4` / 시뮬레이션 Top: `tb_adder4`

- [03.adder4.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/03.adder4/03.adder4.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [03.adder4.srcs/sim_1/new/tb_adder4.v](../projects/03.adder4/03.adder4.srcs/sim_1/new/tb_adder4.v)
- [03.adder4.srcs/sim_1/new/test_bed.v](../projects/03.adder4/03.adder4.srcs/sim_1/new/test_bed.v)
- [03.adder4.srcs/sources_1/imports/new/full_adder.v](../projects/03.adder4/03.adder4.srcs/sources_1/imports/new/full_adder.v)
- [03.adder4.srcs/sources_1/imports/new/half_adder.v](../projects/03.adder4/03.adder4.srcs/sources_1/imports/new/half_adder.v)
- [03.adder4.srcs/sources_1/new/adder4.v](../projects/03.adder4/03.adder4.srcs/sources_1/new/adder4.v)
- [03.adder4.xpr](../projects/03.adder4/03.adder4.xpr)
- [tb_adder4_behav.wcfg](../projects/03.adder4/tb_adder4_behav.wcfg)

## 06.dff_btn_debounce

설계 Top: `top_btn_debounce` / 시뮬레이션 Top: `top_btn_debounce`

- [06.dff_btn_debounce.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/06.dff_btn_debounce/06.dff_btn_debounce.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [06.dff_btn_debounce.srcs/sources_1/new/button_debounce.v](../projects/06.dff_btn_debounce/06.dff_btn_debounce.srcs/sources_1/new/button_debounce.v)
- [06.dff_btn_debounce.srcs/sources_1/new/clock_80Hz.v](../projects/06.dff_btn_debounce/06.dff_btn_debounce.srcs/sources_1/new/clock_80Hz.v)
- [06.dff_btn_debounce.srcs/sources_1/new/D_FF.v](../projects/06.dff_btn_debounce/06.dff_btn_debounce.srcs/sources_1/new/D_FF.v)
- [06.dff_btn_debounce.srcs/sources_1/new/led_toggle.v](../projects/06.dff_btn_debounce/06.dff_btn_debounce.srcs/sources_1/new/led_toggle.v)
- [06.dff_btn_debounce.srcs/sources_1/new/top_btn_debounce.v](../projects/06.dff_btn_debounce/06.dff_btn_debounce.srcs/sources_1/new/top_btn_debounce.v)
- [06.dff_btn_debounce.xpr](../projects/06.dff_btn_debounce/06.dff_btn_debounce.xpr)

## 06_1.btn_debounce_10ms

설계 Top: `top_btn_debounce` / 시뮬레이션 Top: `top_btn_debounce`

- [06_1.btn_debounce_10ms.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [06_1.btn_debounce_10ms.srcs/sources_1/imports/Downloads/button_debounce_10ms.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/imports/Downloads/button_debounce_10ms.v)
- [06_1.btn_debounce_10ms.srcs/sources_1/imports/new/button_debounce.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/imports/new/button_debounce.v)
- [06_1.btn_debounce_10ms.srcs/sources_1/imports/new/clock_80Hz.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/imports/new/clock_80Hz.v)
- [06_1.btn_debounce_10ms.srcs/sources_1/imports/new/D_FF.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/imports/new/D_FF.v)
- [06_1.btn_debounce_10ms.srcs/sources_1/imports/new/led_toggle.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/imports/new/led_toggle.v)
- [06_1.btn_debounce_10ms.srcs/sources_1/imports/new/top_btn_debounce.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/imports/new/top_btn_debounce.v)
- [06_1.btn_debounce_10ms.srcs/sources_1/new/button_debounce_10ms.v](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.srcs/sources_1/new/button_debounce_10ms.v)
- [06_1.btn_debounce_10ms.xpr](../projects/06_1.btn_debounce_10ms/06_1.btn_debounce_10ms.xpr)

## 07.moore_fsm_101_detect

설계 Top: `top_moore_fsm` / 시뮬레이션 Top: `tb_moore_fsm_101`

- [07.moore_fsm_101_detect.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [07.moore_fsm_101_detect.srcs/sim_1/new/tb_moore_fsm_101.v](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.srcs/sim_1/new/tb_moore_fsm_101.v)
- [07.moore_fsm_101_detect.srcs/sources_1/imports/Downloads/button_debounce_10ms.v](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.srcs/sources_1/imports/Downloads/button_debounce_10ms.v)
- [07.moore_fsm_101_detect.srcs/sources_1/imports/new/led_toggle.v](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.srcs/sources_1/imports/new/led_toggle.v)
- [07.moore_fsm_101_detect.srcs/sources_1/new/moore_fsm_101.v](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.srcs/sources_1/new/moore_fsm_101.v)
- [07.moore_fsm_101_detect.srcs/sources_1/new/top_moore_fsm.v](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.srcs/sources_1/new/top_moore_fsm.v)
- [07.moore_fsm_101_detect.xpr](../projects/07.moore_fsm_101_detect/07.moore_fsm_101_detect.xpr)

## 09.up_down_counter

설계 Top: `top` / 시뮬레이션 Top: `top`

- [09.up_down_counter.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/09.up_down_counter/09.up_down_counter.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [09.up_down_counter.srcs/sources_1/imports/Downloads/button_debounce_10ms.v](../projects/09.up_down_counter/09.up_down_counter.srcs/sources_1/imports/Downloads/button_debounce_10ms.v)
- [09.up_down_counter.srcs/sources_1/new/fnd_controller.v](../projects/09.up_down_counter/09.up_down_counter.srcs/sources_1/new/fnd_controller.v)
- [09.up_down_counter.srcs/sources_1/new/main_controller.v](../projects/09.up_down_counter/09.up_down_counter.srcs/sources_1/new/main_controller.v)
- [09.up_down_counter.srcs/sources_1/new/tick_generator.v](../projects/09.up_down_counter/09.up_down_counter.srcs/sources_1/new/tick_generator.v)
- [09.up_down_counter.srcs/sources_1/new/top.v](../projects/09.up_down_counter/09.up_down_counter.srcs/sources_1/new/top.v)
- [09.up_down_counter.xpr](../projects/09.up_down_counter/09.up_down_counter.xpr)

## 10.pwm_control

설계 Top: `top` / 시뮬레이션 Top: `top`

- [10.pwm_control.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/10.pwm_control/10.pwm_control.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [10.pwm_control.srcs/sources_1/imports/Downloads/button_debounce_10ms.v](../projects/10.pwm_control/10.pwm_control.srcs/sources_1/imports/Downloads/button_debounce_10ms.v)
- [10.pwm_control.srcs/sources_1/imports/new/fnd_controller.v](../projects/10.pwm_control/10.pwm_control.srcs/sources_1/imports/new/fnd_controller.v)
- [10.pwm_control.srcs/sources_1/imports/new/tick_generator.v](../projects/10.pwm_control/10.pwm_control.srcs/sources_1/imports/new/tick_generator.v)
- [10.pwm_control.srcs/sources_1/imports/new/top.v](../projects/10.pwm_control/10.pwm_control.srcs/sources_1/imports/new/top.v)
- [10.pwm_control.srcs/sources_1/new/pwm_duty_control.v](../projects/10.pwm_control/10.pwm_control.srcs/sources_1/new/pwm_duty_control.v)
- [10.pwm_control.xpr](../projects/10.pwm_control/10.pwm_control.xpr)

## 999.7bit_full_adder

설계 Top: `adder7` / 시뮬레이션 Top: `tb_adder7`

- [999.7bit_full_adder.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/999.7bit_full_adder/999.7bit_full_adder.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [999.7bit_full_adder.srcs/sim_1/new/tb_adder7.v](../projects/999.7bit_full_adder/999.7bit_full_adder.srcs/sim_1/new/tb_adder7.v)
- [999.7bit_full_adder.srcs/sources_1/new/adder7.v](../projects/999.7bit_full_adder/999.7bit_full_adder.srcs/sources_1/new/adder7.v)
- [999.7bit_full_adder.srcs/sources_1/new/full_adder.v](../projects/999.7bit_full_adder/999.7bit_full_adder.srcs/sources_1/new/full_adder.v)
- [999.7bit_full_adder.xpr](../projects/999.7bit_full_adder/999.7bit_full_adder.xpr)

## adder7

설계 Top: `adder7` / 시뮬레이션 Top: `tb_adder7`

- [adder7.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/adder7/adder7.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [adder7.srcs/sim_1/new/tb_adder7.v](../projects/adder7/adder7.srcs/sim_1/new/tb_adder7.v)
- [adder7.srcs/sources_1/imports/new/full_adder.v](../projects/adder7/adder7.srcs/sources_1/imports/new/full_adder.v)
- [adder7.srcs/sources_1/imports/new/half_adder.v](../projects/adder7/adder7.srcs/sources_1/imports/new/half_adder.v)
- [adder7.srcs/sources_1/new/adder7.v](../projects/adder7/adder7.srcs/sources_1/new/adder7.v)
- [adder7.xpr](../projects/adder7/adder7.xpr)
- [tb_adder7_behav.wcfg](../projects/adder7/tb_adder7_behav.wcfg)

## mealy_fsm

설계 Top: `top_fsm_101_basys3` / 시뮬레이션 Top: `tb_fsm_101_compare`

- [mealy_fsm.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/mealy_fsm/mealy_fsm.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [mealy_fsm.srcs/sim_1/new/tb_fsm_101_compare.v](../projects/mealy_fsm/mealy_fsm.srcs/sim_1/new/tb_fsm_101_compare.v)
- [mealy_fsm.srcs/sources_1/imports/new/button_debounce_10ms.v](../projects/mealy_fsm/mealy_fsm.srcs/sources_1/imports/new/button_debounce_10ms.v)
- [mealy_fsm.srcs/sources_1/imports/new/mealy_fsm.v](../projects/mealy_fsm/mealy_fsm.srcs/sources_1/imports/new/mealy_fsm.v)
- [mealy_fsm.srcs/sources_1/new/button_step.v](../projects/mealy_fsm/mealy_fsm.srcs/sources_1/new/button_step.v)
- [mealy_fsm.srcs/sources_1/new/moore_fsm.v](../projects/mealy_fsm/mealy_fsm.srcs/sources_1/new/moore_fsm.v)
- [mealy_fsm.srcs/sources_1/new/top_fsm_101_basys3.v](../projects/mealy_fsm/mealy_fsm.srcs/sources_1/new/top_fsm_101_basys3.v)
- [mealy_fsm.xpr](../projects/mealy_fsm/mealy_fsm.xpr)

## my_btn_debounce

설계 Top: `top_btn` / 시뮬레이션 Top: `tb_top_btn`

- [my_btn_debounce.srcs/sim_1/new/tb_top_btn.v](../projects/my_btn_debounce/my_btn_debounce.srcs/sim_1/new/tb_top_btn.v)
- [my_btn_debounce.srcs/sources_1/new/btn_debounce.v](../projects/my_btn_debounce/my_btn_debounce.srcs/sources_1/new/btn_debounce.v)
- [my_btn_debounce.srcs/sources_1/new/btn_mux.v](../projects/my_btn_debounce/my_btn_debounce.srcs/sources_1/new/btn_mux.v)
- [my_btn_debounce.srcs/sources_1/new/led_toggle.v](../projects/my_btn_debounce/my_btn_debounce.srcs/sources_1/new/led_toggle.v)
- [my_btn_debounce.srcs/sources_1/new/tick_generator.v](../projects/my_btn_debounce/my_btn_debounce.srcs/sources_1/new/tick_generator.v)
- [my_btn_debounce.srcs/sources_1/new/top_btn.v](../projects/my_btn_debounce/my_btn_debounce.srcs/sources_1/new/top_btn.v)
- [my_btn_debounce.xpr](../projects/my_btn_debounce/my_btn_debounce.xpr)

## my_tick_ledonoff

설계 Top: `top_btn_debounce` / 시뮬레이션 Top: `top_btn_debounce`

- [my_tick_ledonoff.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [my_tick_ledonoff.srcs/sources_1/imports/new/button_debounce.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/imports/new/button_debounce.v)
- [my_tick_ledonoff.srcs/sources_1/imports/new/clock_80Hz.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/imports/new/clock_80Hz.v)
- [my_tick_ledonoff.srcs/sources_1/imports/new/D_FF.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/imports/new/D_FF.v)
- [my_tick_ledonoff.srcs/sources_1/imports/new/led_toggle.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/imports/new/led_toggle.v)
- [my_tick_ledonoff.srcs/sources_1/imports/new/top_btn_debounce.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/imports/new/top_btn_debounce.v)
- [my_tick_ledonoff.srcs/sources_1/new/led_onoff_500ms.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/new/led_onoff_500ms.v)
- [my_tick_ledonoff.srcs/sources_1/new/tick_generator.v](../projects/my_tick_ledonoff/my_tick_ledonoff.srcs/sources_1/new/tick_generator.v)
- [my_tick_ledonoff.xpr](../projects/my_tick_ledonoff/my_tick_ledonoff.xpr)

## project_1

설계 Top: `-` / 시뮬레이션 Top: `-`

복사 대상 소스가 없는 빈 프로젝트 폴더. 학습 구현으로 집계하지 않는다.

## project_2

설계 Top: `mealy_fsm` / 시뮬레이션 Top: `tb_mealy_fsm_101`

- [project_2.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/project_2/project_2.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [project_2.srcs/sim_1/imports/new/tb_moore_fsm_101.v](../projects/project_2/project_2.srcs/sim_1/imports/new/tb_moore_fsm_101.v)
- [project_2.srcs/sources_1/new/mealy_fsm.v](../projects/project_2/project_2.srcs/sources_1/new/mealy_fsm.v)
- [project_2.xpr](../projects/project_2/project_2.xpr)

## pwm_motor

설계 Top: `top` / 시뮬레이션 Top: `top`

- [pwm_motor.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/pwm_motor/pwm_motor.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [pwm_motor.srcs/sources_1/imports/sources_1/imports/Downloads/button_debounce_10ms.v](../projects/pwm_motor/pwm_motor.srcs/sources_1/imports/sources_1/imports/Downloads/button_debounce_10ms.v)
- [pwm_motor.srcs/sources_1/imports/sources_1/imports/new/fnd_controller.v](../projects/pwm_motor/pwm_motor.srcs/sources_1/imports/sources_1/imports/new/fnd_controller.v)
- [pwm_motor.srcs/sources_1/imports/sources_1/imports/new/tick_generator.v](../projects/pwm_motor/pwm_motor.srcs/sources_1/imports/sources_1/imports/new/tick_generator.v)
- [pwm_motor.srcs/sources_1/imports/sources_1/imports/new/top.v](../projects/pwm_motor/pwm_motor.srcs/sources_1/imports/sources_1/imports/new/top.v)
- [pwm_motor.srcs/sources_1/imports/sources_1/new/pwm_duty_control.v](../projects/pwm_motor/pwm_motor.srcs/sources_1/imports/sources_1/new/pwm_duty_control.v)
- [pwm_motor.xpr](../projects/pwm_motor/pwm_motor.xpr)
- [README.md](../projects/pwm_motor/README.md)
- [tests/capture_waveform.tcl](../projects/pwm_motor/tests/capture_waveform.tcl)
- [tests/check_synthesis.tcl](../projects/pwm_motor/tests/check_synthesis.tcl)
- [tests/tb_motor.v](../projects/pwm_motor/tests/tb_motor.v)

## ROM_always

설계 Top: `rom_always` / 시뮬레이션 Top: `rom_always_tb`

- [ROM_always.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/ROM_always/ROM_always.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [ROM_always.srcs/sim_1/new/rom_always_tb.v](../projects/ROM_always/ROM_always.srcs/sim_1/new/rom_always_tb.v)
- [ROM_always.srcs/sources_1/new/rom_always.v](../projects/ROM_always/ROM_always.srcs/sources_1/new/rom_always.v)
- [ROM_always.xpr](../projects/ROM_always/ROM_always.xpr)

## stopwatch

설계 Top: `top` / 시뮬레이션 Top: `tb_tick_generator`

- [stopwatch.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc](../projects/stopwatch/stopwatch.srcs/constrs_1/imports/digilent-xdc-master/Basys3-Master_orginal.xdc)
- [stopwatch.srcs/sim_1/new/tb_button_edge.v](../projects/stopwatch/stopwatch.srcs/sim_1/new/tb_button_edge.v)
- [stopwatch.srcs/sim_1/new/tb_stopwatch.v](../projects/stopwatch/stopwatch.srcs/sim_1/new/tb_stopwatch.v)
- [stopwatch.srcs/sim_1/new/tb_tick_generator.v](../projects/stopwatch/stopwatch.srcs/sim_1/new/tb_tick_generator.v)
- [stopwatch.srcs/sources_1/imports/sources_1/imports/Downloads/button_debounce_10ms.v](../projects/stopwatch/stopwatch.srcs/sources_1/imports/sources_1/imports/Downloads/button_debounce_10ms.v)
- [stopwatch.srcs/sources_1/imports/sources_1/new/fnd_controller.v](../projects/stopwatch/stopwatch.srcs/sources_1/imports/sources_1/new/fnd_controller.v)
- [stopwatch.srcs/sources_1/imports/sources_1/new/tick_generator.v](../projects/stopwatch/stopwatch.srcs/sources_1/imports/sources_1/new/tick_generator.v)
- [stopwatch.srcs/sources_1/new/ani_controller.v](../projects/stopwatch/stopwatch.srcs/sources_1/new/ani_controller.v)
- [stopwatch.srcs/sources_1/new/button_edge.v](../projects/stopwatch/stopwatch.srcs/sources_1/new/button_edge.v)
- [stopwatch.srcs/sources_1/new/mode_controller.v](../projects/stopwatch/stopwatch.srcs/sources_1/new/mode_controller.v)
- [stopwatch.srcs/sources_1/new/time_counter.v](../projects/stopwatch/stopwatch.srcs/sources_1/new/time_counter.v)
- [stopwatch.srcs/sources_1/new/top.v](../projects/stopwatch/stopwatch.srcs/sources_1/new/top.v)
- [stopwatch.xpr](../projects/stopwatch/stopwatch.xpr)

## 원본 참조 누락

- 999.7bit_full_adder: 원본 참조 파일 없음: $PSRCDIR/sources_1/imports/new/full_adder.v
