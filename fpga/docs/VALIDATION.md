# 복사 및 검증 결과

검증 기준일: 2026-10-26. 검증 대상은 보존 파일의 무결성, 선별된 모듈의 시뮬레이션 결과 및 문서 산출물이다.

## 파일 복사

- `projects/`에 원본 입력 파일과 외부 의존 파일 총 123개를 복사하였다.
- 18개 원본 폴더 중 17개에 복사 대상 파일이 있다. `project_1`은 소스 없는 빈 폴더여서 별도 생성하지 않았다.
- XPR 외 파일은 SHA-256으로 원본과 복사본의 바이트 일치를 확인한다. 출처는 `COPY_MANIFEST.csv`에 있다.
- XPR은 텍스트로 다시 저장하였다. `my_btn_debounce.xpr`는 외부 XDC 참조를 `external/Basys3-Master_orginal.xdc`로 수정하였다. 나머지 XPR은 원본 설정을 유지하며 텍스트 줄바꿈만 달라질 수 있다.
- 누락 참조 1건: `999.7bit_full_adder.srcs/sources_1/imports/new/full_adder.v`. 원본에 없는 파일은 임의로 채우지 않았다. 같은 프로젝트에 필요한 반가산기 소스도 없다.

## 시뮬레이션 검증

복사본을 Vivado 2020.2의 xvlog, xelab, XSim 순서로 컴파일·정적 전개·실행하였다. 재실행 스크립트는 작업 라이브러리를 `xil_defaultlib`로 명시한다.

| 대상 | 실행한 테스트 | 결과 | 범위 |
|---|---|---|---|
| pwm_motor | tests/tb_motor.v | PASS | 듀티 0~90%, 경계, 버튼 홀드, 방향, 표시 갱신, 점멸, 리셋 |
| mealy_fsm | tb_fsm_101_compare.v | PASS | Moore/Mealy 출력 관찰 시점 및 중첩 101 시퀀스 비교 |

PWM 테스트 최종 메시지: `PASS: PWM bounds, held button, direction, display updates, blink and reset`.

FSM 테스트 최종 메시지: `PASS: Moore/Mealy 101 comparison`.

PWM 테스트는 PWM 및 FND 관련 모듈을 검증한다. 최상위 전체 입력 경로, 물리 핀 연결, 모터 드라이버 및 오실로스코프 실측은 검증 범위에서 제외하였다. 합성·구현·타이밍 분석·비트스트림 생성·보드 다운로드는 이번 정리에서 실행하지 않았다. 기존 모터 문서에 기록된 합성 검증 이력은 본 재실행 결과와 구분한다.

재실행: PowerShell에서 `./scripts/run_selected_checks.ps1`. Vivado 설치 경로가 다르면 스크립트의 `$vivadoBin`을 변경한다. 실행 결과는 Git에서 제외한 `.tools/validation/`에 생성된다.

## 정적 검토 결과 및 보완 항목

- gate 테스트벤치의 입력 폭 및 미연결 b.
- Moore Top의 `w_clean_btn` / `clean_btn` 신호 불일치.
- 999 가산기의 누락 소스 및 유효하지 않은 XPR 참조.
- my_btn_debounce 외부 XDC의 활성 포트와 실제 Top 포트 불일치.
- my_tick_ledonoff의 신규 모듈과 기존 설계 Top 미통합.
- 06_1의 같은 이름을 가진 debouncer 변형 파일, 원시 입력 갱신 문제.
- 초기 FND 제어기의 불완전한 조합 감지 목록과 Tick/버튼을 별도 클럭으로 사용하는 구조.
- 일부 테스트는 자극만 인가하며 자동 기대값 비교가 없다.

상세 설명은 `FPGA_STUDY.md`에 있다. 해당 항목은 정적 검토에서 확인된 사항이며 전체 설계에 대한 완전성 검증은 수행하지 않았다.

## 문서 확인

한글 맑은 고딕 폰트가 포함된 검색 가능한 PDF를 생성하였다. `scripts/verify_archive.py`에서 페이지가 비어 있지 않은지와 한글 텍스트 및 주요 프로젝트명이 추출되는지 확인한다. PDF 생성과 파일 무결성 검증에는 Python 환경의 `reportlab`, `pypdf`를 사용한다.
