import os
import platform
import sys
from argparse import Namespace
from subprocess import PIPE, Popen

from pyArena import Board, Point, StoneType

from .utils import get_board_string, read, stonetype_to_str, str_to_stonetype, write
from .manager import AgentManager

title = r"""
 ____  _  _  __   ____  ____  __ _   __
(  _ \( \/ )/ _\ (  _ \(  __)(  ( \ / _\
 ) __/ )  //    \ )   / ) _) /    //    \
(__)  (__/ \_/\_/(__\_)(____)\_)__)\_/\_/
"""


def run(args: Namespace):
    turn = 0
    agent = AgentManager(args.board_size, args.black_agent_path, args.white_agent_path)

    while agent.is_finished() is False:
        turn += 1
        now = StoneType.BLACK if turn % 2 == 1 else StoneType.WHITE

        # Clear and Draw Title
        if not args.full_log:
            if platform.system() == "Windows":
                os.system("cls")
            else:
                os.system("clear")
            print(title)

        # Draw Board
        agent.print_board()

        print(f"turn: {turn} player: {stonetype_to_str(now)}")
        x, y = agent.genmove(now)
        agent.play(now, x, y)

    winner = "Black" if agent.get_winner() == StoneType.BLACK else "White"
    print(f"winner: {winner}")
    sys.exit(0)


if __name__ == "__main__":
    run()
