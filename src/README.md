# 2021 HAI RL Arena - C++ API
2021년 2학기 한양대학교 인공지능 동아리 HAI에서 열린 따목 대회의 C++ API입니다.

## 빠른 시작

### 사전 작업

Windows의 경우, 아래의 공식 링크문서를 참고하여 WSL을 설치하기 위한 과정을 완료하여 주시기 바랍니다.

[https://docs.microsoft.com/ko-kr/windows/wsl/install-win10](https://docs.microsoft.com/ko-kr/windows/wsl/install-win10)

cmd에 아래의 코드를 입력하여 필요한 것들을 설치합니다.

```bash
$> sudo apt install python3-distutils

$> sudo apt install python3-dev  # for python3.x installs

$> sudo apt install git
```

레포지토리를 로컬에 복제하여 사용하기 위한 단계입니다. 적절한 위치에서 아래 명령어를 입력합니다.

```bash
$> git clone --recursive https://github.com/HanyangTechAI/2021-HAI-RL-Arena
```

### 대회 시작

**가. 저는 Agent를 Python으로 구현할래요!**

2021-HAI-RL-Arena/src 위치 이동하여 `pyAgent`를 설치해줍니다.

```bash
$> cd 2021-HAI-RL-Arena/src
$> pip install .
```

2021-HAI-RL-Arena/src/Extension/pyArenaPlayer 위치로 이동하여 `pyAgentPlayer`를 설치해줍니다.

```bash
$> cd Extension/pyArenaPlayer
$> pip install .
```

그 다음, 원하는 위치에서 여러분의 agent를 구현합니다. (예제에서는 example_agent.py)

> `src/example_agent.py`를 참고해주세요!

```python
from pyArena import Agent, Board, StoneType, Point

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

	def Play(self, color: StoneType, point: Point) -> None:
		...

	def TimeLeft(self, black_time: int, white_time: int) -> None:
		...

	def ClearBoard(self) -> None:
		...
```

만드신 Agent와 직접 따목을 해보시려면 아래와 같이 pyArenaPlayer를 사용해주세요!

[자세한 사용법은 여기를 참고해주세요!](https://github.com/HanyangTechAI/2021-HAI-RL-Arena/tree/master/src/Extension/pyArenaPlayer)
```bash
$> pyarena --black-agent-path example_agent.py
```

**나. 저는 Agent를 C++로 구현할래요!**

우선, src폴더에 원하시는 Agent 이름으로 폴더를 만들어주세요!

```bash
# YourAgentName은 원하시는 이름으로 바꿔주세요!
$> cd 2021-HAI-RL-Arena/src && mkdir YourAgentName
```

그 다음, 만드신 Agent 폴더 안에 아래와 같은 CMakeLists.txt를 작성합니다.

```
set(target YourAgentName)

add_executable(${target} main.cc)

target_link_libraries(${target} PRIVATE Arena)
```

이후, main.cc를 만들고, 그 안에 Agent를 상속하여 여러분만의 따목 Agent를 구현합니다.

> `src/RandomBot`의 `main.cc`를 참고해주세요!

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

	void Play(StoneType color, const Point& pt) {
		...
	}

	void ClearBoard() {
		...
	}
	
	...
}
```

만든 Agent를 빌드시키기 위해 **src폴더**의 CMakeLists.txt아래에 다음을 추가합니다.
```
add_subdirectory(YourAgentName)
```

그 후, src 폴더에서 아래 코드로 빌드를 진행합니다.

```bash
$> mkdir build && cd build
$> cmake ..
$> make -j
```

## API 구조

**Agent**에 대한 API 문서입니다. 대회 당일날 실행하게될 코드입니다.

(C++)      [https://www.notion.so/Agent-5de622c33aa14fec8fc704de254a021f](https://www.notion.so/Agent-5de622c33aa14fec8fc704de254a021f)

(Python)  [https://www.notion.so/Agent-de00ba42ce684ce3a1fdc4d3d079dee2](https://www.notion.so/Agent-de00ba42ce684ce3a1fdc4d3d079dee2)

---

**Board**에 대한 API 문서입니다. 대회 서버에서 아래 Board로 게임 진행이 처리되므로, Agent 구현 시 적절히 사용해주세요.

(C++)      [https://www.notion.so/Board-0ae28fcf5edf48918e6a1773fb4da5ce](https://www.notion.so/Board-0ae28fcf5edf48918e6a1773fb4da5ce)

(Python)  [https://www.notion.so/Board-bc39d429fd1249e8a5b2054abde51f2f](https://www.notion.so/Board-bc39d429fd1249e8a5b2054abde51f2f)

---

추가적으로 **Types**에서는 다음과 같은 타입들을 사용할 수 있습니다.

```cpp
StoneType.BLACK // 검정색 StoneType
StoneType.WHITE // 하얀색 StoneType
StoneType.INVALID // 알 수 없는 StoneType

Point(X, Y) // 바둑판의 좌표를 설정.
