# 2021 HAI RL Arena - C++ API
2021년 2학기 한양대학교 인공지능 동아리 HAI에서 열린 따목 대회의 C++ API입니다.

## 빠른 시작

### 사전 작업

Windows의 경우, 아래의 공식 링크문서를 참고하여 WSL을 설치하기 위한 과정을 완료하여 주시기 바랍니다.

[https://docs.microsoft.com/ko-kr/windows/wsl/install-win10](https://docs.microsoft.com/ko-kr/windows/wsl/install-win10)

cmd에 아래의 코드를 입력하여 필요한 것들을 설치합니다.

```bash
sudo apt install python3-distutils

sudo apt install python3-dev  # for python3.x installs

sudo apt install git

# git config --global user.name [이름]
# git config --global user.mail [메일 주소]
```

레포지토리를 로컬에 복제하여 사용하기 위한 단계입니다. 적절한 위치(예를 들면 Documents 폴더 안)에서 아래의 코드를 cmd에 입력합니다.

(Windows)
```bash
git clone --recursive https://github.com/HanyangTechAI/2021-HAI-RL-Arena
```

(Linux)
```bash
git clone --recursive https://github.com/HanyangTechAI/2021-HAI-RL-Arena.git
```

가. C++

2021-HAI-RL-Arena/cpp 위치로 이동합니다. 이동한 후 아래의 코드를 입력합니다.

```bash
cd cpp

mkdir build && cmake .. && make -j
```

나. Python

2021-HAI-RL-Arena/cpp 위치로 이동합니다. 이동한 후 아래의 코드를 입력합니다.

```bash
pip install .
```

2021-HAI-RL-Arena/cpp/Extension/pyArenaPlayer 위치로 이동합니다. 이동한 후 아래의 코드를 입력합니다.

```bash
pip install .
```

기존에 만든 .py 파일을 이용하여 실행시키려면 다음과 같이 입력합니다.

```bash
cd lib
python3 mybadugi.py
```

### 대회 시작하기

파이썬의 경우, 필요한 라이브러리를 import합니다. 만약 import가 되지 않는다면, 이전 단계를 다시 확인해보는 것이 권장됩니다.

```bash
import pyArena as ar
```

또는,

```bash
from pyArena import Agent, Board, StoneType, Point
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

**Agent**에 대한 API 문서입니다.

(C++)      [https://www.notion.so/Agent-5de622c33aa14fec8fc704de254a021f](https://www.notion.so/Agent-5de622c33aa14fec8fc704de254a021f)

(Python)  [https://www.notion.so/Agent-de00ba42ce684ce3a1fdc4d3d079dee2](https://www.notion.so/Agent-de00ba42ce684ce3a1fdc4d3d079dee2)

---

**Board**에 대한 API 문서입니다.

(C++)      [https://www.notion.so/Board-0ae28fcf5edf48918e6a1773fb4da5ce](https://www.notion.so/Board-0ae28fcf5edf48918e6a1773fb4da5ce)

(Python)  [https://www.notion.so/Board-bc39d429fd1249e8a5b2054abde51f2f](https://www.notion.so/Board-bc39d429fd1249e8a5b2054abde51f2f)

---

상속에 대한 설명입니다. Agent를 상속하여 커스텀 에이전트(custom-agent)를 구현할 때는 아래 부분을 참고하여 설계를 진행합니다. C++, Python 모두 "상속"의 개념을 지원하므로 각각에 대해 아래의 기본 구조를 따라 진행하시면 됩니다.

가. C++

```cpp
class MyAgent: public Agent {
	// 생성자
	MyAgent(...) {
		...
	}

	// Agent에서 virtual로 선언된 부분은 모두 구현합니다.
	void BoardSize(int boardSize) {
		...
	}

	void TimeSetting(int timesPerMove) {
		...
	}

	Point GenMove(StoneType color) {
		...
	}

	void Play(StoneType oppColor, const Point& pt) {
		...
	}

	void ClearBoard() {
		...
	}

	void custom_method(...) {
		...
	}
	...
}
```

나. Python

```python
class MyAgent(Agent):
	def __init__(self, name: str):
		super().__init__(name)
		...

	def BoardSize(self, size: int) -> None:
		self.board_size = size
		self.board = Board(size)
		...

	def GenMove(self, color: StoneType) -> Point:
		...

	def Play(self, opp_color: StoneType, point: Point) -> None:
		...

	def TimeLeft(self, black_time: int, white_time: int) -> None:
		...

	def ClearBoard(self) -> None:
		...
```
