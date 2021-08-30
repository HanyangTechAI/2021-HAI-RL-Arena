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

    void TimeLeft(int blackTime, int whiteTime) override
    {
        PYBIND11_OVERRIDE_PURE(void, Agent, TimeLeft, blackTime, whiteTime);
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
        .def("BoardSize", &Agent::BoardSize)
        .def("TimeLeft", &Agent::TimeLeft)
        .def("GenMove", &Agent::GenMove)
        .def("Play", &Agent::Play)
        .def("ClearBoard", &Agent::ClearBoard)
        .def("Run", &Agent::Run);
}
