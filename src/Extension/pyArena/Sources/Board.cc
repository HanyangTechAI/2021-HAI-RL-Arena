#include <pybind11/stl.h>

#include <pyArena/Board.h>

#include <Arena/Board.hpp>

namespace py = pybind11;
using namespace Arena;

void buildBoard(py::module& m)
{
    py::class_<Board>(m, "Board")
        .def(py::init<int>())
        .def("GetBoardSize", &Board::GetBoardSize)
        .def("IsOnBoard", &Board::IsOnBoard)
        .def("IsValidMove", &Board::IsValidMove)
        .def("IsKo", &Board::IsKo)
        .def("IsSuicide", &Board::IsSuicide)
        .def("At", &Board::At)
        .def("IsFinished", &Board::IsFinished)
        .def("GetCurrentPlayer", &Board::GetCurrentPlayer)
        .def("GetWinner", &Board::GetWinner)
        .def("Play", &Board::Play);
}
