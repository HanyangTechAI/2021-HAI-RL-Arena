# 2021 HAI RL Arena - C++ API
2021년 2학기 한양대학교 인공지능 동아리 HAI에서 열린 따목 대회의 C++ API입니다.

## 빠른 시작

### 사전 작업

Windows의 경우, 아래의 공식 링크문서를 참고하여 WSL을 설치하기 위한 과정을 완료하여 주시기 바랍니다.

[https://docs.microsoft.com/ko-kr/windows/wsl/install-win10](https://docs.microsoft.com/ko-kr/windows/wsl/install-win10)

cmd에 아래의 코드를 입력하여 필요한 것들을 설치합니다.

```bash
sudo apt install python3-distutils

sudo apt-get install python3-dev  # for python3.x installs

sudo apt-get install git

# git config --global user.name [이름]
# git config --global user.mail [메일 주소]
```

레포지토리를 로컬에 복제하여 사용하기 위한 단계입니다. 적절한 위치(예를 들면 Documents 폴더 안)에서 아래의 코드를 cmd에 입력합니다.

```bash
git clone https://github.com/JYPark09/2021-HAI-RL-Arena
```

2021-HAI-RL-Arena/cpp 위치로 이동합니다. 이동한 후 아래의 코드를 입력합니다.

```bash
cd cpp

mkdir build && cmake .. && make -j
```

이제 마지막 단계입니다. lib 폴더로 이동한 후, python을 실행시킬 수 있다면 모든 준비가 다 되었습니다.

```bash
cd lib
python3
```

### 대회 시작하기

필요한 라이브러리를 import합니다. 만약 import가 되지 않는다면, 이전 단계를 다시 확인해보는 것이 권장됩니다.

```bash
import pyArena as ar
```

에이전트(Agent) 객체 하나를 생성합니다. 이때, 인자로 string형의 이름을 넣어야 합니다. 아래의 예시는 "test"라는 이름을 가진 에이전트를 생성한 모습입니다.

```bash
ag = ar.Agent("test")
```

이제 보드판을 만들 차례입니다. 아래의 코드를 통해 바둑 보드판 Board 객체 하나를 생성합니다. 바둑판은 일반적으로 가로, 세로는 각각 19개의 줄을 가지고 있으므로, 인자로 19를 넣어 객체를 생성합니다.

```bash
board = ar.Board(19)
```

## API 구조
