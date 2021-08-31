import os
import sys
from subprocess import PIPE, Popen

from pyArena import Board, Opponent, Point, StoneType

from .utils import get_board_string, read, stonetype_to_str, write


class AgentManager:
    """
    Agent Manager class for communicating with agents

    :param board_size: Size of board
    :param black_agent_path: (Optional) Black agent's source path
    :param white_agent_path: (Optional) White agent's source path
    """

    def __init__(self, board_size, black_agent_path=None, white_agent_path=None):
        _black_agent_path = (
            os.path.join(os.path.dirname(__file__), "player_agent.py")
            if black_agent_path is None
            else black_agent_path
        )
        _white_agent_path = (
            os.path.join(os.path.dirname(__file__), "player_agent.py")
            if white_agent_path is None
            else white_agent_path
        )

        self.board_size = board_size
        self.board = Board(board_size)
        self.is_human = {
            "b": black_agent_path is None,
            "w": white_agent_path is None,
        }
        self.players = {
            "b": Popen(
                [
                    sys.executable,
                    "-u",
                    _black_agent_path,
                    "--board-size",
                    str(board_size),
                ],
                stdin=PIPE,
                stdout=PIPE,
                stderr=PIPE,
            ),
            "w": Popen(
                [
                    sys.executable,
                    "-u",
                    _white_agent_path,
                    "--board-size",
                    str(board_size),
                ],
                stdin=PIPE,
                stdout=PIPE,
                stderr=PIPE,
            ),
        }

        for player in self.players.keys():
            write(self.players[player], "board_size " + str(board_size) + "\n")
            read(self.players[player])

    def genmove(self, color: StoneType):
        """
        Get a move from the player

        :return: coordinates x and y
        """
        now = stonetype_to_str(color)
        genmove_payload = "genmove " + now + "\n"
        write(self.players[now], genmove_payload)

        # If human, get input from user
        if self.is_human[now]:
            while True:
                try:
                    move = input("your_move(ex: A 1 )[q to exit]: ")
                    if move == "q":
                        write(self.players[now], "quit\n")
                        self.quit()
                        sys.exit(0)

                    move = move.split()
                    x = int(move[1])
                    y = ord(move[0]) - ord("A") + 1

                    assert self.board.IsValidMove(Point(x, y))
                    break
                except Exception as e:
                    print(f"Invalid Move, Got Error: {e}")
                    pass

            write(self.players[now], str(x) + " " + str(y) + "\n")

        # Get genmove output coordinates (x, y)
        out = read(self.players[now]).split()
        return int(out[1]), int(out[2])

    def play(self, color: StoneType, x: int, y: int):
        """
        Play a move

        :param color: Stone color
        :param x: x coordinate
        :param y: y coordinate
        """
        now = stonetype_to_str(color)
        opponent = stonetype_to_str(Opponent(color))
        play_payload = "play " + now + " " + str(x) + " " + str(y) + "\n"

        # Write play info to now player
        write(self.players[now], play_payload)
        read(self.players[now])

        # Write play info to opponent player
        write(self.players[opponent], play_payload)
        read(self.players[opponent])

        self.board.Play(Point(x, y), color)

    def quit(self):
        """
        Quit the game
        """
        for player in self.players.keys():
            write(self.players[player], "quit\n")

    def is_finished(self):
        """
        Check if the game is finished

        :return: True if finished, False otherwise
        """
        return self.board.IsFinished()

    def print_board(self):
        """
        Print the board
        """
        print(get_board_string(self.board, self.board_size))

    def get_winner(self):
        """
        Get the winner

        :return: Color of the winner
        """
        return self.board.GetWinner()
