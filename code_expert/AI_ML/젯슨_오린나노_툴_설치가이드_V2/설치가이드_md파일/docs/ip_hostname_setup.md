# IP & Host Name setup

## 고정 IP setup: ubunut 기반

ssh terminal 환경에서 `nmcli`로 wired connection IP manual setup 방법

### 1. connection status

아래 명령으로 connection 정보를 확인한다. `NAME` 정보를 기반으로 setup을 진행한다.

```bash
    nmcli c show
```

`Wired connection 1`을 기반으로 진행 예

### 2. IP와 게이트웨이를 동시에 설정 (서브넷 마스크 /24 포함)

`xx`: 고정 ip 변호로 수정하고 아래 명령을 수행

```bash
sudo nmcli c modify "Wired connection 1" \
    ipv4.addresses 10.10.141.xx/24 \
    ipv4.gateway 10.10.141.254
```

### 3. 할당 방식을 '수동(manual)'으로 변경

```bash
sudo nmcli c modify "Wired connection 1" \
    ipv4.method manual
```

### 4. DNS도 같이 설정해주는 것이 좋습니다 (안 그러면 이름 해석이 안 될 수 있음)

```bash
sudo nmcli c modify "Wired connection 1" \
    ipv4.dns "8.8.8.8,8.8.4.4"
```

### 5. 설정 적용

```bash
sudo nmcli connection up "Wired connection 1"
```

---

## Host Name setup

`mDNS`를 사용하여 연력하기 위해 고유의 Host Name을 지정한다.

### 1. 현재 호스트 이름 확인

터미널을 열고 아래 명령어를 입력하여 현재 이름을 확인합니다.

```bash
hostnamectl

```

### 2. 호스트 이름 변경

`jetson-xxx`(xxx 는 수강 번호)로 변경 예

```bash
sudo hostnamectl set-hostname jetson-000

```

### 3. hosts 파일 수정 (중요)

호스트 이름만 바꾸면 네트워크상에서 혼선이 생기거나, `sudo` 명령어를 쓸 때 `unable to resolve host` 에러가 발생할 수 있음. 이를 방지하기 위해 `/etc/hosts` 파일도 수정.

```bash
sudo vi /etc/hosts

```

파일이 열리면 보통 두 번째 줄에 있는 기존 이름을 **새로운 이름**으로 변경

* **수정 전:** `127.0.1.1  ubuntu`
* **수정 후:** `127.0.1.1  jetson-000`

### 4. 시스템 재부팅

변경 사항을 완전히 적용하려면 시스템을 재부팅 권장

```bash
sudo reboot

```

---

### 💡 팁

* **이름 규칙:** 호스트 이름에는 영문 소문자, 숫자, 하이픈(`-`)만 사용하는 것이 관례입니다. 공백이나 특수문자는 피한다.
* **확인:** 재부팅 후 터미널 프롬프트(`user@jetson-000:~$`)에서 바뀐 이름을 바로 확인할 수 있다.
