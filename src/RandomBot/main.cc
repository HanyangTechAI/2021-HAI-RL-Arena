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

    Arena::Point GenMove(Arena::StoneType color) override
    {
        std::uniform_int_distribution<int> dist(0, boardSize_);

        const int X = dist(engine);
        const int Y = dist(engine);

        if (X == 0 || Y == 0)
            return Arena::Resign;

        return Arena::Point{ X, Y };
    }

    void Play(Arena::StoneType color, const Arena::Point& pt) override
    {
        (void)color;
        (void)pt;
    }

    void TimeLeft(int blackTime, int whiteTime) override
    {
        leftTimes_[0] = blackTime;
        leftTimes_[1] = whiteTime;
    }

    void ClearBoard() override
    {
    }

 private:
    int boardSize_{ 0 };
    int timesPerMove_{ 0 };
    int leftTimes_[2]{ 0 };

    std::mt19937 engine;
};

int main()
{
    RandomBot bot;

    bot.Run();
}
