# Python pyArena Player

pyArena를 플레이할 수 있는 플레이어입니다.

## How to Run
```shell
# 프로젝트 cpp폴더에서 pyArena를 설치합니다.
$> cd pyArena/cpp && pip install .
$> cd Extension/pyArenaPlayer && pip install .

$> pyarena
```

## Arguments
```shell
$> pyarena --help

usage: pyarena [-h] [--black-agent-path BLACK_AGENT_PATH] [--white-agent-path WHITE_AGENT_PATH] [--full-log]

optional arguments:
  -h, --help            show this help message and exit

agent info:
  사용할 Agent들의 위치

  --black-agent-path BLACK_AGENT_PATH
                        흑돌의 Agent 위치
  --white-agent-path WHITE_AGENT_PATH
                        백돌의 Agent 위치
  --full-log            화면을 지우지 않고 모든 로그를 남깁니다.

```
