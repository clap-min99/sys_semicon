# Troubleshooting on Windows system
  NVIDIA SDK manager windows version(이하 SM)은 windows의 상태에 따라 여러 문제를 발생 시킨다.

## Firewall
  * SM은 `usbipd`을 통해 jetson board와 통신하여 SDK를 install한다.
  * `usbipd`이 사용하는 port `3240`이 막혀 있는 경우 SDK install은 실패한다.
  * powershell을 관리자 권한으로 열고 아래 명령을 통해 `3240` port를 `usbipd`에게 허락해 주어야 한다.

    ```powershell
    New-NetFirewallRule -DisplayName "usbipd" -Direction Inbound -Action Allow -Protocol TCP -LocalPort 3240 -Program "C:\Program Files\usbipd-win\usbipd.exe"
    ```

  * 문제가 지속될 경우 아래 명령으로 `usbipd`을 다시 시작한다.

    ```powershell
    Restart-Service usbipd
    ```

## IP 수동 설정: on Jetson
  * 강의장 LAN router가 DHCP를 제공하는데 외부연결을 차단하고 있는 경우 IP를 수동 설정을 진행한다
    * gateway와 DNS 설정을 다음 절차에 따라 수정하여 주어야 한다.

      ```bash
      # IP와 gateway 설정: xx 자리를 자신의 ip로 설정
      sudo nmcli connection modify "Wired connection 1" ipv4.addresses 10.10.15.xx/24 ipv4.gateway 10.10.15.254
      # DNS 설정
      sudo nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8,8.8.4.4"
      # IP 할당을 수동으로 수정
      sudo nmcli connection modify "Wired connection 1" ipv4.method manual
      # 설정 적용
      sudo nmcli connection up "Wired connection 1"
      ```
    
