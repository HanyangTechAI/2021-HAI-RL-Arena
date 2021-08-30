from pyArena import Board, Point, StoneType


def get_board_string(board: Board, board_size: int):
    """
    Return a string representation of the board.

    :param board: The board to be printed.
    :returns: A string representation of the board.
    """
    board = _get_board_array(board, board_size)

    board_size = len(board)
    board_str = "   "

    for i in range(board_size):
        board_str += str(chr(ord("A") + i)) + " "
    board_str += "\n"

    for i in range(board_size):
        board_str += f"{str(i + 1):>2}" + " "
        for j in range(board_size):
            if board[i][j] == int(StoneType.BLACK):
                board_str += "⚫"
            elif board[i][j] == int(StoneType.WHITE):
                board_str += "⚪"
            else:
                board_str += ". "
        board_str += "\n"

    return board_str


def _get_board_array(board: Board, board_size: int):
    """
    Return an array representation of the board.

    :param board: Arena board class
    :param board_size: The size of the board.
    :returns: An array representation of the board.
    """
    board_array = []
    for i in range(1, board_size + 1):
        board_row = []
        for j in range(1, board_size + 1):
            point = Point(i, j)
            stone_type = board.At(point)
            if stone_type == StoneType.BLACK:
                board_row.append(1)
            elif stone_type == StoneType.WHITE:
                board_row.append(2)
            else:
                board_row.append(0)
        board_array.append(board_row)

    return board_array


def read(process):
    """
    Read line from process

    :param process: The process to read from.
    :returns: The line read from the process.
    """
    return process.stdout.readline().decode("utf-8").strip()


def write(process, message):
    """
    Read line from process

    :param process: The process to write.
    :param message: The message to write.
    :returns: The line read from the process.
    """
    process.stdin.write(f"{message.strip()}\n".encode("utf-8"))
    process.stdin.flush()


if __name__ == "__main__":
    board = [
        [2, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 2],
    ]
    print(get_board_string(board))
