import re
from .game import run

from argparse import ArgumentParser

# fmt: off
parser = ArgumentParser()
group = parser.add_argument_group(title="agent info", description="사용할 Agent들의 위치")
group.add_argument("--black-agent-path", type=str, required=True, help="흑돌의 Agent 위치")
group.add_argument("--white-agent-path", type=str, required=True, help="백돌의 Agent 위치")
group.add_argument("--black-human", action='store_true', help="흑돌이 사람일 경우")
group.add_argument("--white-human", action='store_true', help="백돌이 사람일 경우")
# fmt: on

args = parser.parse_args()
run(args)
