import os
import platform
import sys
from argparse import Namespace
from subprocess import PIPE, Popen

from pyArena import Board, Point, StoneType

from .utils import get_board_string, read, write

title = r"""
 ________  ___    ___ ________  ________  _______   ________   ________
|\   __  \|\  \  /  /|\   __  \|\   __  \|\  ___ \ |\   ___  \|\   __  \
\ \  \|\  \ \  \/  / | \  \|\  \ \  \|\  \ \   __/|\ \  \\ \  \ \  \|\  \
 \ \   ____\ \    / / \ \   __  \ \   _  _\ \  \_|/_\ \  \\ \  \ \   __  \
  \ \  \___|\/  /  /   \ \  \ \  \ \  \\  \\ \  \_|\ \ \  \\ \  \ \  \ \  \
   \ \__\ __/  / /      \ \__\ \__\ \__\\ _\\ \_______\ \__\\ \__\ \__\ \__\
    \|__||\___/ /        \|__|\|__|\|__|\|__|\|_______|\|__| \|__|\|__|\|__|
         \|___|/
"""


def run(args: Namespace):
    board_size = 10
    turn = 0

    black_agent_path = (
        os.path.join(os.path.dirname(__file__), "player_agent.py")
        if args.black_agent_path is None
        else args.black_agent_path
    )
    white_agent_path = (
        os.path.join(os.path.dirname(__file__), "player_agent.py")
        if args.white_agent_path is None
        else args.white_agent_path
    )

    players = {
        "b": Popen(
            [sys.executable, "-u", black_agent_path],
            stdin=PIPE,
            stdout=PIPE,
            stderr=PIPE,
        ),
        "w": Popen(
            [sys.executable, "-u", white_agent_path],
            stdin=PIPE,
            stdout=PIPE,
            stderr=PIPE,
        ),
    }
    is_human = {
        "b": args.black_agent_path is None,
        "w": args.white_agent_path is None,
    }
    stone_type = {
        "b": StoneType.BLACK,
        "w": StoneType.WHITE,
    }

    board = Board(board_size)

    for player in players.keys():
        write(players[player], ("board_size " + str(board_size) + "\n"))
        out = read(players[player])

    while board.IsFinished() is False:
        turn += 1
        if turn % 2 == 1:
            now, opponent = "b", "w"
        else:
            now, opponent = "w", "b"

        if not args.full_log:
            if platform.system() == "Windows":
                os.system("cls")
            else:
                os.system("clear")
            print(title)

        print(get_board_string(board, board_size))

        print(f"turn: {turn} player: {now}")
        genmove_payload = "genmove " + now + "\n"
        write(players[now], genmove_payload)
        if is_human[now]:
            while True:
                try:
                    move = input("your_move(ex: 1 A )[q to exit]: ")
                    if move == "q":
                        players["b"].send_signal(9)
                        players["w"].send_signal(9)
                        sys.exit(0)

                    move = move.split()
                    x = int(move[0])
                    y = ord(move[1]) - ord("A") + 1

                    assert board.IsValidMove(Point(x, y))
                    break
                except Exception as e:
                    print(e)
                    pass

            write(players[now], str(x) + " " + str(y) + "\n")

        out = read(players[now]).split()
        play_payload = "play " + now + " " + out[1] + " " + out[2] + "\n"
        board.Play(Point(int(out[1]), int(out[2])), stone_type[now])
        write(players[opponent], play_payload)
        read(players[opponent])

    winner = "Black" if board.GetWinner() == StoneType.BLACK else "White"
    print(get_board_string(board, board_size))
    print(f"winner: {winner}")


if __name__ == "__main__":
    run()
