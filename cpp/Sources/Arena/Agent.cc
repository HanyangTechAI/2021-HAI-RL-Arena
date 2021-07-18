#include <Arena/Agent.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace Arena
{
Agent::Agent(std::string name) : name_(std::move(name))
{
}

void Agent::Run()
{
    bool isRun = true;

    std::string line;
    while (isRun && std::getline(std::cin, line))
    {
        std::transform(begin(line), end(line), begin(line), ::tolower);

        std::istringstream iss(line);
        std::vector<std::string> tokens(
            (std::istream_iterator<std::string>(iss)),
            std::istream_iterator<std::string>());

        if (tokens.empty())
            continue;

        if (tokens[0] == "name")
        {
            std::cout << "= " << name_ << std::endl;
        }
        else if (tokens[0] == "board_size")
        {
            const int boardSize = std::stoi(tokens[1]);
            BoardSize(boardSize);

            std::cout << "=" << std::endl;
        }
        else if (tokens[0] == "time_setting")
        {
            const int timesPerMove = std::stoi(tokens[1]);
            TimeSetting(timesPerMove);

            std::cout << "=" << std::endl;
        }
        else if (tokens[0] == "genmove")
        {
            const StoneType color = parseStoneType(tokens[1]);
            const Point move = GenMove(color);

            std::cout << "= " << move.X << " " << move.Y << std::endl;
        }
        else if (tokens[0] == "play")
        {
            const StoneType oppColor = parseStoneType(tokens[1]);
            const Point move{ std::stoi(tokens[1]), std::stoi(tokens[2]) };
            Play(oppColor, move);

            std::cout << "=" << std::endl;
        }
        else if (tokens[0] == "clear_board")
        {
            ClearBoard();

            std::cout << "=" << std::endl;
        }
        else if (tokens[0] == "quit")
        {
            isRun = false;
        }
    }
}

StoneType Agent::parseStoneType(const std::string& token) const
{
    if (token == "b" || token == "black")
        return StoneType::BLACK;

    if (token == "w" || token == "white")
        return StoneType::WHITE;

    return StoneType::INVALID;
}
}  // namespace Arena
