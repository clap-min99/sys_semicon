# PWM DC 모터 과제

Vivado 2020.2 / Basys3 / 시스템 클럭 100 MHz.
기존 PWM 주파수 10 MHz, 듀티 0~90%(10% 간격), 리셋 시 50%를 유지한다.

## 조작과 표시

| SW1(IN2) | SW0(IN1) | 동작 | FND 예시(50%) |
|---|---|---|---|
| 1 | 0 | 정회전 | F050 |
| 0 | 1 | 역회전 | b050 |
| 1 | 1 | 정지 | 공백 + 050 |
| 0 | 0 | 방향 표시 없음 | 공백 + 050 |

천의 자리 방향 문자만 1초 켜짐 / 1초 꺼짐으로 깜박인다(전체 주기 2초).
위 표의 SW1은 논리 입력 sw[1]이며, 과제 PDF에 맞춰 V16(보드의 물리 SW3)에 연결한다.
따라서 실제 조작 스위치는 SW0(V17, IN1)와 SW3(V16, IN2)이다.
7세그먼트에서는 f를 F 모양으로 표현한다. 백·십·일의 자리는 듀티 백분율을 표시한다.
btnU(T18)는 10% 증가, btnD(U17)는 10% 감소하며 길게 눌러도 한 번만 변경된다.
리셋은 기존 설정대로 SW15(R2), btnC는 기존 코드에서 기능이 없다.
정지 시 방향선은 11이고 PWM 출력과 듀티 설정은 유지된다.

## 배선

| 출력 | FPGA 패키지 핀 | 보드 커넥터 | 용도 |
|---|---|---|---|
| pwm_out | J1 | JA1 | 모터 드라이버 PWM 입력 |
| in1_in2[0] | L2 | JA2 | IN1 |
| in1_in2[1] | J2 | JA3 | IN2 |
| pwm_scope | A15 | JB7 | 오실로스코프 측정용 PWM 복제 |

과제의 A15는 FPGA 패키지 핀 이름이며, 보드에서 점퍼를 연결할 위치는 **JB7**이다.
오실로스코프 프로브 팁을 JB7에, 접지 클립을 PMOD GND에 연결한다.
모터는 외부 드라이버를 통해 연결하며 FPGA 핀에 직접 연결하지 않는다.

듀티 000에서는 JA1과 JB7 모두 LOW여야 한다. 계속 회전한다면 PWM이 실제 드라이버의
EN/PWM 입력에 연결됐는지, 공통 GND가 연결됐는지, 보드에 최신 비트스트림을 다운로드했는지 확인한다.
L298N 모듈의 ENA/ENB 점퍼가 해당 채널을 항상 활성화하는 구성이라면,
전원을 끈 후 해당 EN 점퍼를 제거하고 JA1 PWM을 그 EN 입력에 연결한다.
드라이버 종류와 회로에 따라 연결 방법이 다르므로 모델 확인이 먼저다.

## 파형 분석과 촬영

기존 카운터는 100 MHz 클럭 10개마다 반복하므로 T = 100 ns, f = 10 MHz다.
듀티 D = HIGH 시간 / 주기 × 100%. 버튼은 HIGH 시간을 10 ns씩 변경한다.

| FND 듀티 | 예상 HIGH 시간 | 예상 LOW 시간 | 주파수 |
|---|---|---|---|
| 000 | 0 ns | 항상 LOW | 펄스 없음 |
| 010 | 10 ns | 90 ns | 10 MHz |
| 030 | 30 ns | 70 ns | 10 MHz |
| 050 | 50 ns | 50 ns | 10 MHz |
| 070 | 70 ns | 30 ns | 10 MHz |
| 090 | 90 ns | 10 ns | 10 MHz |

Vivado XSim에서 0~90% 모든 단계의 HIGH 클럭 수와 상·하한, 버튼 홀드,
방향 문자, 정지 표시, 데이터 갱신, 깜박임, 리셋을 검증했다.
깜박임 테스트는 BLINK_CYCLES=100으로 가속하고 실제 회로 기본값은 100,000,000이다.
시뮬레이션 파형은 `tests/motor_waveform.vcd`에 저장한다.

실물 촬영은 보드와 오실로스코프에서 수행해야 한다. 위 표는 계산값과 RTL 검증 결과이며 실측 결과가 아니다.
10X 프로브, DC 결합, 상승 에지 트리거, 약 20 ns/div로 시작해 화면에 2~3주기를 표시한다.
btnU/btnD로 10%, 50%, 90%를 선택하고 FND와 화면의 주기·주파수·양의 펄스폭·듀티를 촬영한다.
10%와 90%에서는 가장 짧은 펄스가 10 ns이므로 프로브와 장비 대역폭에 따라 모서리가 둥글게 보일 수 있다.

| 설정 | 실측 주기 | 실측 HIGH 시간 | 실측 듀티 | 촬영 파일 |
|---|---|---|---|---|
| 10% | 미측정 | 미측정 | 미측정 | 미촬영 |
| 50% | 미측정 | 미측정 | 미측정 | 미촬영 |
| 90% | 미측정 | 미측정 | 미측정 | 미촬영 |

분석 문장 예시: “듀티 설정 증가에 따라 HIGH 시간이 증가하며 주기는 약 100 ns로 유지된다.”
실측 후에는 해당 수치와 계산값의 오차를 함께 기록한다.

## 검증 재실행 (PowerShell)

```powershell
$sources = @(Get-ChildItem pwm_motor.srcs/sources_1 -Recurse -Filter *.v | ForEach-Object { $_.FullName })
xvlog --work xil_defaultlib @sources tests/tb_motor.v
xelab xil_defaultlib.tb_motor -debug typical -s motor_assignment_test
xsim motor_assignment_test -tclbatch tests/capture_waveform.tcl
vivado -mode batch -source tests/check_synthesis.tcl -log tests/synthesis.log -journal tests/synthesis.jou
```

테스트 로그의 `PASS`를 확인한다. 보드 다운로드 전 Vivado에서 구현과 비트스트림 생성을 실행한다.
