#include <pyArena/Agent.h>
#include <pyArena/Board.h>
#include <pyArena/Types.h>

PYBIND11_MODULE(pyArena, m) {
    m.doc() = R"pbdoc(HAIArena reinforcement learning agent)pbdoc";

    buildAgent(m);
    buildBoard(m);
    buildPointStruct(m);
    buildStoneTypeEnum(m);
    buildOpponentFunc(m);
}
