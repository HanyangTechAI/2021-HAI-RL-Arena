import os
import sys
from subprocess import PIPE, Popen
from argparse import Namespace

from pyArena import Board, Point, StoneType

from .utils import get_board_string, read, write


def run(args: Namespace):
    board_size = 10
    turn = 0

    players = {
        "b": Popen(
            [sys.executable, "-u", args.black_agent_path],
            stdin=PIPE,
            stdout=PIPE,
            stderr=PIPE,
        ),
        "w": Popen(
            [sys.executable, "-u", args.white_agent_path],
            stdin=PIPE,
            stdout=PIPE,
            stderr=PIPE,
        ),
    }
    is_human = {
        "b": args.black_human,
        "w": args.white_human,
    }
    stone_type = {
        "b": StoneType.BLACK,
        "w": StoneType.WHITE,
    }

    board = Board(board_size)

    for player in players.keys():
        write(players[player], ("board_size " + str(board_size) + "\n"))
        out = read(players[player])

    while board.IsFinished() == False:
        turn += 1
        if turn % 2 == 1:
            now, opponent = "b", "w"
        else:
            now, opponent = "w", "b"

        os.system("clear")
        print(get_board_string(board, board_size))

        print(f"turn: {turn} player: {now}")
        genmove_payload = "genmove " + now + "\n"
        write(players[now], genmove_payload)
        if is_human[now]:
            while True:
                try:
                    move = input("your_move(ex: 1 A): ")
                    move = move.split()
                    x = int(move[0])
                    y = ord(move[1]) - ord("A") + 1

                    assert board.IsValidMove(Point(x, y))
                    break
                except:
                    print("invalid move")
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
