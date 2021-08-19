#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <pyArena/Types.h>

#include <Arena/Types.hpp>

namespace py = pybind11;
using namespace Arena;

void buildPointStruct(py::module& m) {
    py::class_<Point>(m, "Point")
        .def(py::init<int, int>())
        .def(py::self == py::self)
        .def(py::self != py::self);
}

void buildStoneTypeEnum(py::module& m) {
    py::enum_<StoneType>(m, "StoneType")
        .value("NONE", StoneType::NONE)
        .value("BLACK", StoneType::BLACK)
        .value("WHITE", StoneType::WHITE)
        .value("INVALID", StoneType::INVALID);
}
