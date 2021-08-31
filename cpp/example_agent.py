from pyArena import Agent, Board, Point, StoneType


class ExampleAgent(Agent):
    """
    남는 공간에 순서대로 돌을 놓는 예제 Agent 입니다.

    :param name: 에이전트의 이름.
    """

    def __init__(self, name: str):
        super().__init__(name)
        self.board = None
        self.board_size = None

    def BoardSize(self, size: int) -> None:
        """
        서버로부터 판의 크기를 받았을 때 호출됩니다.

        :param size: 판의 줄 수.
        """
        self.board_size = size
        self.board = Board(size)

    def GenMove(self, color: StoneType) -> Point:
        """
        서버에게 다음 수를 요청받았을 때 호출됩니다.
        예제 Agent에서는 보이는 맨 첫 번째 빈 공간에 착수합니다.

        :param color: 착수할 돌의 색깔.
        :return: 생성된 착수 위치.
        """
        for i in range(1, self.board_size + 1):
            for j in range(1, self.board_size + 1):
                point = Point(i, j)
                if self.board.IsValidMove(point) and not self.board.IsSuicide(
                    point, color
                ):
                    return point

        return Point(-1, -1)

    def Play(self, opp_color: StoneType, point: Point) -> None:
        """
        상대방이 착수한 위치와 상대방의 색깔 정보를 받았을 때 호출됩니다.

        :param opp_color: 상대방의 돌 색깔.
        :param point: 상대방의 착수 위치.
        """
        self.board.Play(point, opp_color)

    def TimeLeft(self, black_time: int, white_time: int) -> None:
        """
        흑/백 각자에게 남은 시간 정보를 받았을 때 호출됩니다.

        :param black_time: 흑에게 남은 시간(초)
        :param white_time: 백에게 남은 시간(초)
        """
        pass

    def ClearBoard(self) -> None:
        """
        서버로부터 판의 초기화 명령이 들어오면 호출됩니다.
        """
        self.board = Board(self.board_size)


if __name__ == "__main__":
    agent = ExampleAgent("ExampleAgent")
    agent.Run()
