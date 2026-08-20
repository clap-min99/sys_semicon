# Jetson Orin Nano: Docker on SSD

## Docker setup

### 1. check docker status

* 아래 명령으로 docker info를 확인한다.
  ```bash
  docker info
  ```

* `permission denied while trying to connect to the docker API at unix:///var/run/docker.sock`
* 권한 문제: 매번 sudo 사용하는대신 `USER`를 docker group에 추가

  ```bash
  sudo usermod -aG docker $USER
  newgrp docker
  ```

<!-- ```bash
$ sudo nvidia-ctk runtime configure --runtime=docker
INFO[0000] Config file does not exist; using empty config 
INFO[0000] Wrote updated config to /etc/docker/daemon.json 
INFO[0000] It is recommended that docker daemon be restarted. 
``` -->

* docker status 확인: 기본 setting `runc`

    ```bash
    $ docker info |grep -e Runtime -e Root
    Runtimes: io.containerd.runc.v2 nvidia runc
    Default Runtime: runc
    Docker Root Dir: /var/lib/docker
    ```

### 2. Docker config for GPU

> Default Runtime을 nvidia로 바꾸어 GPU를 사용하게 설정

* /etc/docker/daemon.json File 수정 전

    ```bash
    $ cat /etc/docker/daemon.json 
    {
        "runtimes": {
            "nvidia": {
                "args": [],
                "path": "nvidia-container-runtime"
            }
        }
    }
    ```

* 수정

    ```bash
    sudo jq '. + {"default-runtime": "nvidia"}' /etc/docker/daemon.json | \
    sudo tee /etc/docker/daemon.json.tmp && \
    sudo mv /etc/docker/daemon.json.tmp /etc/docker/daemon.json
    ```

* 수정 후

    ```bash
    {
    "runtimes": {
        "nvidia": {
        "args": [],
        "path": "nvidia-container-runtime"
        }
    },
    "default-runtime": "nvidia"
    }
    ```

* Restart docker

    ```bash
    sudo systemctl daemon-reload && sudo systemctl restart docker
    ```

### 3. Final verification

* **Default Runtime: `nvidia`**

    ```bash
    $ docker info | grep -e Runtime -e Root
    Runtimes: io.containerd.runc.v2 nvidia runc
    Default Runtime: nvidia
    Docker Root Dir: /var/lib/docker
    ```
