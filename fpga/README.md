# FPGA 디지털 회로 설계 학습 기록

Basys3와 Verilog HDL을 이용한 디지털 회로 설계 실습의 소스 및 기술 문서 저장소이다. `D:\project\fpga\ai2`의 프로젝트를 기준으로 학습 주제, 구현 구조, 검증 결과 및 개선 과제를 정리하였다.

## 문서

- [학습 보고서 — Markdown](docs/FPGA_STUDY.md)
- [학습 보고서 — PDF](docs/FPGA_STUDY.pdf)
- [프로젝트별 코드 목록](docs/CODE_INDEX.md)
- [복사 파일 출처 및 원본 SHA-256](docs/COPY_MANIFEST.csv)
- [검증 결과 및 재실행 방법](docs/VALIDATION.md)

## 학습 범위

논리 게이트, 반가산기·전가산기, 다비트 가산기, 조합 ROM, 플립플롭, 버튼 디바운싱, Tick 생성, Moore·Mealy FSM, 카운터, FND, 시계·스톱워치 및 PWM 모터 제어를 포함한다. 학습 순서는 코드의 개념적 의존 관계를 기준으로 구성하였다.

## 개발 환경 및 파일 구성

- 보드 및 디바이스: Basys3 / Artix-7 / `xc7a35tcpg236-1`.
- 도구: Vivado 2020.2, Verilog HDL, XSim.
- 기준 클럭: 주요 설계 기준 100 MHz.
- `projects/`: 17개 프로젝트의 RTL, 테스트벤치, XDC, XPR, 파형 설정 및 테스트 스크립트.
- `docs/`: 학습 보고서, 코드 목록, 복사 이력 및 검증 결과.
- `scripts/`: 원본 파일 복사, PDF 생성, 무결성 확인 및 선별 테스트 실행 도구.

## 프로젝트 실행

1. Vivado 2020.2에서 대상 폴더의 `.xpr` 파일을 실행한다.
2. Sources에서 설계 Top과 Simulation Top을 확인한다.
3. 검증 문서에 기록된 소스 누락, 연결 오류 및 XDC 정합성 문제를 확인한다.
4. 시뮬레이션 후 합성, 구현 및 비트스트림 생성을 수행한다.

동일 이름의 모듈이 프로젝트별로 존재하므로 소스는 프로젝트 단위로 관리한다. `my_btn_debounce`의 외부 XDC는 `external/`에 보존하였으나 활성 제약과 현재 최상위 포트 사이의 불일치 수정이 필요하다.

## 검증 현황

`pwm_motor`의 PWM·표시 테스트와 `mealy_fsm`의 Moore·Mealy 비교 테스트는 XSim 재실행에서 PASS를 확인하였다. 전체 프로젝트의 합성·구현·타이밍 분석 및 보드 실측은 본 정리의 검증 범위에 포함되지 않는다.

## Git 관리 기준

관리 대상은 `README.md`, `.gitignore`, `docs/`, `projects/`, `scripts/`이다. Vivado 생성 파일과 로컬 문서 생성 라이브러리는 제외한다. 기존 루트의 강의 PDF·PPTX는 로컬에 보관하며, `docs/FPGA_STUDY.pdf`는 문서 산출물로 관리한다. 커밋 및 원격 업로드는 수행하지 않았다.

## 문서 및 검증 도구

Python 3.11 이상과 `reportlab`, `pypdf`가 필요하다. 로컬 `.tools/python` 경로의 라이브러리도 검색 대상에 포함된다.

```powershell
python scripts/render_study_pdf.py
python scripts/verify_archive.py
./scripts/run_selected_checks.ps1
```

테스트 실행 시 Vivado 설치 경로는 `scripts/run_selected_checks.ps1`의 `$vivadoBin` 설정을 따른다.
