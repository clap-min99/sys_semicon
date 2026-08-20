# Jetson Orin Nano: SSD setup guid

SDK manager를 통하여 기본 tool과 SDK를 install한 경우에 대한 setup guide를 정리한다.

## 1. Jetson에 SSH을 통해 login 

* powershell을 열고 아래 명령으로 jetson board에 login 한다.
  ```powershell
  ssh –Y aidl@jetson-000.local
  ```

* 처음 연결 시 연결 진행 여부를 묻는 message가 출력됨. `yes`를 입력하고 진행
* `host name으로 연결이 안될 경우 ip로 진행한다.
* passwd를 입력하고 login 한다.
* login 되면 아래 명령으로 ubuntu update 와 upgrade를 진행한다.

    ```bash
    sudo apt update
    sudo apt upgrade
    ```

## 1. install tools

<!-- * python3-pip

    ```bash
    sudo apt install python3-pip
    ```

* jetson-stats

    ```bash
    sudo -H pip3 install -U jetson-stats
    ``` -->

* check cuda version

    ```bash
    nvcc --version
    ```

* nvcc가 없다고 나오면 아래 명령으로 `cuda/bin` 을 PATH에 추가

    ```bash
    echo 'export PATH=/usr/local/cuda/bin:$PATH' >> ~/.bashrc
    echo 'export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
    ```

* `cuda-tookit-12` install

    ```bash
    sudo apt install cuda-toolkit-12
    ```

* `nvidia-container`, `apt-utils`: to save time, `jq`: For docker configuration

    ```bash
    sudo apt install -y nvidia-container apt-utils jq
    ```

* `jetson-stats`을 아래 명령을 이용하여 super user 권한으로 install : for `jtop`  

    ```bash
    sudo -H pip3 install -U jetson-stats
    ```

* reboot system

    ```bash
    sudo reboot
    ```

* jtop에서 jetpack version missing issue: 아래 file을 수정, 진행하지 않는다.

    ```bash
    sudo vi /usr/local/lib/python3.10/dist-packages/jtop/core/jetson_variables.py
    ```

### 💡 tip

* jetpack version을 정확히 확인하는 방법

    ```bash
    sudo apt-cache show nvidia-jetpack | grep "Version:"
    ```
