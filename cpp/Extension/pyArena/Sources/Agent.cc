#include <pybind11/stl.h>

#include <pyArena/Agent.h>

#include <Arena/Agent.hpp>
#include <Arena/Types.hpp>

namespace py = pybind11;
using namespace Arena;

class PyAgent : public Agent
{
 public:
    // Inherit the constructors
    using Agent::Agent;

    void BoardSize(int boardSize) override
    {
        PYBIND11_OVERRIDE_PURE(void, Agent, BoardSize, boardSize);
    }


    Point GenMove(StoneType color) override
    {
        PYBIND11_OVERRIDE_PURE(Point, Agent, GenMove, color);
    }

    void Play(StoneType oppColor, const Point& pt) override
    {
        PYBIND11_OVERRIDE_PURE(void, Agent, Play, oppColor, pt);
    }

    void ClearBoard() override
    {
        PYBIND11_OVERRIDE_PURE(void, Agent, ClearBoard);
    }

    void TimeLeft(int blackTime, int whiteTime) override
    {
        PYBIND11_OVERRIDE_PURE(void, Agent, TimeLeft, blackTime, whiteTime);
    }
};

void buildAgent(py::module& m)
{
    py::class_<Agent, PyAgent>(m, "Agent")
        .def(py::init<std::string>())
        .def("board_size", &Agent::BoardSize)
        .def("gen_move", &Agent::GenMove)
        .def("play", &Agent::Play)
        .def("clear_board", &Agent::ClearBoard)
        .def("time_left", &Agent::TimeLeft)
        .def("run", &Agent::Run);
}