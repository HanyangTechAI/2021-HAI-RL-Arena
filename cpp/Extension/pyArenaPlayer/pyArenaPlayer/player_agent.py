import sys

from pyArena import Agent, Board, Point, StoneType


class PlayerAgent(Agent):
    """
    An agent that can communicate with user shell.

    :param name: Agent's name
    """

    def __init__(self, name: str):
        super().__init__(name)
        self.board = None
        self.board_size_ = 10

    def BoardSize(self, size: int) -> None:
        """
        Set the board size.

        :param board_size: Board size
        """
        self.board_size_ = size
        self.board = Board(size)

    def TimeSetting(self, times_per_move: int) -> None:
        """
        Set the time setting.

        :param times_per_move: Time setting
        """
        pass

    def GenMove(self, color: StoneType) -> Point:
        """
        Called when the agent is asked to generate a move.

        :param color: Color of the next move
        :return: A point
        """
        while True:
            move = sys.stdin.readline().strip().split()
            try:
                if len(move) <= 1:
                    raise ValueError(move)

                x = int(move[0])
                y = int(move[1])
                point = Point(x, y)

                if not self.board.IsValidMove(point):
                    raise ValueError("Invalid Move")

                self.board.Play(point, color)
                return point

            except ValueError as e:
                print(e)

    def Play(self, opp_color: StoneType, point: Point) -> None:
        """
        Called when the agent is asked to play a move.

        :param opp_color: Opponent's color
        :param point: A point
        """
        self.board.Play(point, opp_color)

    def TimeLeft(self, black_time: int, white_time: int) -> None:
        """
        Called when the agent has less time left.

        :param black_time: Black time left
        :param white_time: White time left
        """
        pass

    def ClearBoard(self) -> None:
        """
        Called when the agent is asked to clear the board.
        """
        self.board = Board(self.board_size_)


if __name__ == "__main__":
    agent = PlayerAgent("Player")
    agent.Run()
