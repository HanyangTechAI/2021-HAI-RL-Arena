from argparse import ArgumentParser

from .game import run

# fmt: off
parser = ArgumentParser()
group = parser.add_argument_group(title="agent info", description="사용할 Agent들의 위치")
group.add_argument("--black-agent-path", type=str, help="흑돌의 Agent 위치")
group.add_argument("--white-agent-path", type=str, help="백돌의 Agent 위치")
group.add_argument("--full-log", action='store_true', help="화면을 지우지 않고 모든 로그를 남깁니다.")
# fmt: on

args = parser.parse_args()
run(args)
