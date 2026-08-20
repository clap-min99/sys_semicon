# Jetson Image flashing on SSD w/ NVIDIA SDK manager

## 목차

 [1. SDK Manager](#1-sdk-manager-실행)
 
 [2. SSD flashing](#2-ssd-flashing)
 
 [3. Troubleshooting](./trouble_shooting.md)

## 주의 사항

* NVIDIA SDK nanager는 기본적으로 linux 기반의 tool이다. 따라서 windows system에서도 WSL을 사용한다.
  * WSL을 먼저 install 하고 진행한다.
    * powershell에서 아래 명령으로 wsl을 install 한다.

    ```powershell
    wsl --install
    ```

  * 아래그림과 같이 진행이 멈추는 경우 아래 명령을 powershell에서 관리자 권한으로 실행한다.

    ```powershell
    # 가상 머신 플랫폼 기능 활성화
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
    # Linux용 Windows 하위 시스템 기능 활성화
    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
    ```

    ![wsl_hu](./images/wsl_hup.png)

  * system을 restart한다.
  * 다시한번 wsl install을 실행하고 배포판 리스트가 출력되면 아래 명령으로 `Ubuntu`를 install한다.
 
    ```powershell
    wsl --install -d Ubuntu
    ```
    
* WSL 환경하에서 USB port on/off를 진행하며 이 때 powershell을 사용한다.
  * powershell은 가장 최신인 7.6.x를 install 하기를 추천한다.
  * 제공한 `.msi`를 이용하여 설치 후 환경변수 `PATH`에 이 folder를 추가하고 우선권을 최상으로 한다.
  ![fig](./images/powershell_path.png)
* Downloading 과 install을 동시 진행할 경우 시간이 많이 걸린다.
  * 수업에서는 먼저 Downloading을 진행하고 시차를 두고 install을 진행한다.

## 1. SDK manager 실행

 SDK manager 실행하고 login 후 Download 진행

* 실행 초기화면

  ![fig1](./images/sdk_1.png)
* login click -> login on web-browser (web browser): 계정이 없으면 만들어야 함
  ![fig2](./images/sdk_2.png)
* mail을 확인하라는 message (web browser)

  ![fig3](./images/sdk_3.png)
* NVIDIA에서 보내온 메일에서 `Verify`를 눌러 검증

  ![fig4](./images/sdk_4.png)
* Email Authentication 완료

  ![fig5](./images/sdk_5.png)
* NVIDIA SDK signing 진행 (web browser)

  ![fig6](./images/sdk_6.png)
* SDK signing 완료 (web browser)

  ![fig7](./images/sdk_7.png)
* SDK login 진행

  ![fig8](./images/sdk_8.png)
* SDK login 완료 후 new version info : `Later` 선택

  ![fig9](./images/sdk_9.png)
* SDK `Step 01`

  ![fig10](./images/sdk_10.png)
  * SDK `Step 01`: `Target Hardware`를 진행 -> `Jetson Orin Nano modules`
  
  ![fig11](./images/sdk_11.png)
* SDK `Step 02`: `TARGET COMPONENTS` 모두를 선택, `lincense`와 `Download` 선택

  ![fig12](./images/sdk_12.png)
* SDK `Step 03`: Download 진행

  ![fig13](./images/sdk_13.png)
* SDK `Step 04`

  ![fig14](./images/sdk_14.png)

## 2. SSD flashing

* Board 준비
  * image flashing 을 위해 Jetson을 `Rescue` mode로 setting
    * J14(Bustton Header) pin 10,`Force Recovery`pin을 `GND`에 jumper로 연결
  * USB port 연결

    ![fig_jetson](./images/jetson_rescue.png)

* Tool 설치
  * [usbip-win](https://github.com/dorssel/usbipd-win/releases): USB로 IP 연결 시 사용
    * 제공한 `usbipd-win_5.3.0_x64.msi`를 실행
    * 인스톨 후 아래 명령으로 확인해 보자

      ```powershell
      usbipd list
      ```

* `APX driver`: 보드 연결시 없으면 아래와 같이 popup이 뜬다.
  ![APX](./images/APX_driver.png)
  
  * SDK manager 종료하고 APX driver를 인스톨한다.
   * 제공한 `zadig-2.9.exe`(APX driver installer)를 실행 -> 추가정보 -> 실행 -> 인스톨
   * SDK manager 다시 실행
---
* SDK `Step 01`: 보드 연결을 자동으로 확인

    ![fig15](./images/sdk_15.png)

  * 보드 연결시 APX driver가 없으면 아래와 같이 popup이 뜬다.

     ![APX](./images/APX_driver.png)

    * SDK manager 종료하고 APX driver를 인스톨한다.
    * 제공한 `zadig-2.9.exe`(APX driver installer)를 실행 -> 추가정보 -> 실행 -> 인스톨
    * SDK manager 다시 실행
    
 * SDK `Product` selection: 보드 연결이 되면 자동으로 선택 popup이 뜬다
   * `Jeson Orin Nano[8GB developer kit version]` 선택
  
  ![fig16](./images/sdk_16.png)
 * SDK `Step 02`: `Lincese` 만 check하고 진행
   * 주의 사항: `TARGET COMPONENT` 전체 선택 확인 필수
  
   ![fig17](./images/sdk_17.png)
* SDK `OEM Configuration` & `Storage`: 초기 login 필요, 반드시 아래와 같이 지정한다.
  * New Username: `aidl`
  * New Password: `will`
  * Sotrage Device: `NVMe`
  * `Flash`로 다음 진행
  
  ![fig18](./images/sdk_18.png)
* SDK `Step 03`: `Download only` 를 unmark 하고 진행

  ![fig19](./images/sdk_19.png)
* com port 를 이용하여 jetson b'd 에 login한다. (연결 방법은 [여기](./jetson_usb_login.md)를 참고한다.)
  * jetson b'd의 ip를 확인한다.
* `SDK components` install 시작 전에 확인 창이 뜬다.

  ![fig20](./images/sdk_20.png)
* connection을 `USB`에서 `Wthernet`으로 바꾸고 확인한 ip를 적어 준다.

  ![fig20-1](./images/sdk_eth_01.png)
* `Install`을 선택하고 진행
* `verifying Jetson board` 후 진행 됨

  ![fig21](./images/sdk_21.png)
* SDK `Step 04`

  ![fig22](./images/sdk_22.png)

## 3. OEM setup 마무리

* SDK Installation이 끝나면 전원과 rescue mode 점퍼와 usb를 제거한다.
* 키보드, 마우스, 모니터를 연결하고 전원을 인가하여 정상 부팅을 진행한다.

* `aidl` user로 login하고 초기 setup을 진행한다.
* `Power Mode`를 `max`로 바꾼다.
* network setup을 진행한다.
  * `ifconfig` 명령으로 ip를 확인하고 기록한다.
* 아래 명령으로 `hostname`을 `jetson-xxx`로 수정한다.
  * `xxx`는 본인의 수강 번호를 세자리로 표현. 예: 7번 --> `jetson-007`
  ```bash
  sudo hostnamectl set-hostname jetson-007
  ```
* `/etc/hosts` file안의 정보도 수정
  * 수정 전
    ```Plaintext
    127.0.0.1   localhost
    127.0.1.1   ubuntu
    ```

  * 수정 후
    ```Plaintext
    127.0.0.1   localhost
    127.0.1.1   jetson-007
    ```
* 다음 명령으로 jetson을 poweroff한 뒤 전원을 분리한다.

  ```bash
  sudo poweroff
  ```

* jetson board를 `Headless` mode로 전환한다.
  * 키보드, 마우스, 모니터를 분리한다.

## 4. 전원을 연결하고 ssh로 login하자

* 아래 명령을 powershell에서 실항하여 ssh로 login해 보자
  ```Poswershell
  ssh -Y aidl@jetson-007
  ```

  * 연결이 안되면 기록해둔 IP로 연결해 보자
  ```Powershell
  ssh -Y aidl@192.168.1.59
  ```
* 처음 연결하면 연결진행 여부를 묻는다. `yes`하고 login 진행
* passwd를 입력하고 login 한다.
* 아래 명령으로 ubuntu를 update한다.
  ```bash
  sudo apt update
  sudo apt upgrade
  ```
