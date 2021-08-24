#ifndef PYARENA_TYPES_H
#define PYARENA_TYPES_H

#include <pybind11/pybind11.h>

void buildPointStruct(pybind11::module& m);
void buildResignStruct(pybind11::module& m);
void buildStoneTypeEnum(pybind11::module& m);
void buildOpponentFunc(pybind11::module& m);

#endif  // PYARENA_TYPES_H
