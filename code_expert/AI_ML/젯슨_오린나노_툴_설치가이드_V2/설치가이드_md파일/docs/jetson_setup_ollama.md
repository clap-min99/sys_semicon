# Ollama quick install guid

## 1. Install Ollama

* 아래 명열으로  ollama를 install 한다.
  ```bash
  curl -fsSL https://ollama.com/install.sh | sh
  ```

* curl (Client URL): 터미널(CLI) 환경에서 URL을 이용해 서버와 데이터를 주고받거나, 서버에 특정 기능(요청)을 수행하도록 명령하는 도구
* `-fsSL` : option, `에러가 나면 조용히 실패하고, 진행은 숨기되, 올바른 주소로 자동 이동해서 데이터를 가져와`

  1. `f`: `fail`을 무시
  2. `s`: `silence`, 진행 상황 숨기기
  3. `S`: `Show`, 치명적인 에러 보이기
  4. `L`: `Location`, redirect 주소 추적

* `|`: `pipe`, 읽어온 data를 다음 명령 `sh`에 전달하여 수행

## 2. Pull a model: donwload model

* 아래 명령으로 `gemma3:4b` model을 download한다.

  ```bash
  ollama pull gemma3:4b
  ```

## 3. 현재 Swap 메모리 확인하기

터미널에서 다음 명령어를 입력하여 현재 설정된 Swap 용량을 확인하세요.

```bash
free -h
```

또는 더 상세한 정보를 보려면:

```bash
swapon --show
```

* `Swap`: 항목의 `Total` 용량이 **16G** 이상 확보, 원활한 LLM model 구동을 위해

---

## 4. Swap 메모리 늘리기 (Step-by-Step)

**기존 Swap을 끄고 16GB로 새로 설정**하는 방법

### ① 기존 Swap 비활성화 (선택 사항)

```bash
sudo swapoff -a
```

### ② Swap 파일 생성 (16GB 기준)

`fallocate` 명령어를 사용하여 16GB 크기의 파일을 생성

```bash
sudo fallocate -l 16G /swapfile
```

### ③ 권한 설정 (보안상 중요)

```bash
sudo chmod 600 /swapfile
```

### ④ Swap 포맷 및 활성화

```bash
sudo mkswap /swapfile
sudo swapon /swapfile
```

## 5. 재부팅 후에도 자동 적용하기

위 설정은 재부팅하면 사라짐. 영구적으로 적용하려면 `/etc/fstab` 파일을 다음과 같이 수정.

1. 파일 열기:

```bash
sudo vi /etc/fstab

```

2. 파일 맨 아래에 다음 내용을 추가하고 저장 후 종료:

```text
/swapfile none swap sw 0 0

```

## 6. 확인 및 마무리

다시 `free -h`를 입력하여 `Swap: Total`이 **16Gi** 근처로 나오는지 확인.

---

## 💡 vLLM vs Ollama 비교 요약

| 구분 | **vLLM** (기업/서버급) | **Ollama** (개인/에지급) |
| --- | --- | --- |
| **주요 목표** | 고처리량(High Throughput), 서빙 효율화 | 간편한 사용, 개인화된 로컬 실행 |
| **메모리 관리** | **PagedAttention** (메모리 선점형) | 온디맨드(On-demand) 동적 할당 |
| **설정 난이도** | 높음 (Jetson 전용 빌드/설정 필요) | 매우 낮음 (스크립트 한 줄 설치) |
| **추천 하드웨어** | 넉넉한 VRAM (Orin NX, AGX 이상) | 제한된 리소스 (**Orin Nano 8GB**) |
| **장점** | 여러 명이 동시 접속해도 속도 저하 적음 | 설치가 쉽고 다양한 양자화 모델 지원 |
