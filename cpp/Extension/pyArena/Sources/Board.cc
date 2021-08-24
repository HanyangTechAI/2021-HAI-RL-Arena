#include <pybind11/stl.h>

#include <pyArena/Board.h>

#include <Arena/Board.hpp>

namespace py = pybind11;
using namespace Arena;

void buildBoard(py::module& m)
{
    py::class_<Board>(m, "Board")
        .def(py::init<int>())
        .def("get_board_size", &Board::GetBoardSize)
        .def("is_on_board", &Board::IsOnBoard)
        .def("is_valid_move", &Board::IsValidMove)
        .def("is_ko", &Board::IsKo)
        .def("is_suicide", &Board::IsSuicide)
        .def("at", &Board::At)
        .def("is_finished", &Board::IsFinished)
        .def("get_current_player", &Board::GetCurrentPlayer)
        .def("get_winner", &Board::GetWinner)
        .def("play", &Board::Play);
}
