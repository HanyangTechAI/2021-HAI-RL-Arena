#include <Arena/Agent.hpp>

#include <random>

class RandomBot final : public Arena::Agent
{
 public:
    RandomBot() : Agent("RandomBot"), engine(std::random_device()())
    {
    }

    void BoardSize(int boardSize) override
    {
        boardSize_ = boardSize;
    }

    void TimeSetting(int timesPerMove) override
    {
        timesPerMove_ = timesPerMove;
    }

    Arena::Point GenMove(Arena::StoneType color) override
    {
        std::uniform_int_distribution<int> dist(-1, boardSize_ - 1);

        const int X = dist(engine);
        const int Y = dist(engine);

        if (X == -1 || Y == -1)
            return Arena::Resign;

        return Arena::Point{ X, Y };
    }

    void Play(Arena::StoneType oppColor, Arena::Point pt) override
    {
        (void)oppColor;
        (void)pt;
    }

    void ClearBoard() override
    {
    }

 private:
    int boardSize_{ 0 };
    int timesPerMove_{ 0 };

    std::mt19937 engine;
};

int main()
{
    RandomBot bot;

    bot.Run();
}
