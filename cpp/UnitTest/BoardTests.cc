#include <doctest.h>

#include <iostream>

#include <Arena/Board.hpp>

using namespace Arena;

TEST_CASE("[Board] Construction Tests")
{
    Board board9x9(9);
    CHECK_EQ(board9x9.GetBoardSize(), 9);
    CHECK_EQ(board9x9.GetCurrentPlayer(), StoneType::BLACK);
    CHECK_EQ(board9x9.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(board9x9.IsFinished());

    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= 9; ++j)
        {
            CHECK_EQ(board9x9.At(Point{ i, j }), StoneType::NONE);
        }
    }

    Board board15x15(15);
    CHECK_EQ(board15x15.GetBoardSize(), 15);
    CHECK_EQ(board15x15.GetCurrentPlayer(), StoneType::BLACK);
    CHECK_EQ(board15x15.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(board15x15.IsFinished());

    for (int i = 1; i <= 15; ++i)
    {
        for (int j = 1; j <= 15; ++j)
        {
            CHECK_EQ(board15x15.At(Point{ i, j }), StoneType::NONE);
        }
    }

    Board board19x19(19);
    CHECK_EQ(board19x19.GetBoardSize(), 19);
    CHECK_EQ(board19x19.GetCurrentPlayer(), StoneType::BLACK);
    CHECK_EQ(board19x19.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(board19x19.IsFinished());

    for (int i = 1; i <= 19; ++i)
    {
        for (int j = 1; j <= 19; ++j)
        {
            CHECK_EQ(board19x19.At(Point{ i, j }), StoneType::NONE);
        }
    }
}

TEST_CASE("[Board] Basic Play Tests")
{
    Board bd(19);

    CHECK_FALSE(bd.IsValidMove(Point{ 0, 0 }));

    bd.Play(Point{ 10, 10 });
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.GetCurrentPlayer(), StoneType::WHITE);
    CHECK_EQ(bd.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(bd.IsFinished());

    bd.Play(Point{ 1, 1 });
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 1, 1 }), StoneType::WHITE);
    CHECK_EQ(bd.GetCurrentPlayer(), StoneType::BLACK);
    CHECK_EQ(bd.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(bd.IsFinished());

    bd.Play(Point{ 10, 11 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.GetCurrentPlayer(), StoneType::WHITE);
    CHECK_EQ(bd.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(bd.IsFinished());

    bd.Play(Point{ 10, 12 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 12 }), StoneType::BLACK);
    CHECK_EQ(bd.GetCurrentPlayer(), StoneType::WHITE);
    CHECK_EQ(bd.GetWinner(), StoneType::INVALID);
    CHECK_FALSE(bd.IsFinished());
}

TEST_CASE("[Board] Capture One Test")
{
    Board bd(19);

    bd.Play(Point{ 10, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 11 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    bd.Play(Point{ 9, 10 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    bd.Play(Point{ 10, 9 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    bd.Play(Point{ 11, 10 }, StoneType::WHITE);

    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::WHITE);
}

TEST_CASE("[Board] Capture Many Tests")
{
    Board bd(19);

    bd.Play(Point{ 10, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 11 }, StoneType::BLACK);
    bd.Play(Point{ 9, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 9 }, StoneType::BLACK);
    bd.Play(Point{ 11, 10 }, StoneType::BLACK);

    bd.Play(Point{ 10, 8 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 9, 9 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 8, 10 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 9, 11 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 10, 12 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 11, 11 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 12, 10 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::BLACK);

    bd.Play(Point{ 11, 9 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 10 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 10, 11 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 9, 10 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 10, 9 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 11, 10 }), StoneType::NONE);
}

TEST_CASE("[Board] Capture One at Corner Test")
{
    Board bd(19);

    // 11시 방향에서 테스트
    bd.Play(Point{ 1, 1 }, StoneType::BLACK);

    bd.Play(Point{ 1, 2 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 1, 1 }), StoneType::BLACK);

    bd.Play(Point{ 2, 1 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 1, 1 }), StoneType::NONE);

    // 5시 방향에서 테스트
    bd.Play(Point{ 19, 19 }, StoneType::WHITE);

    bd.Play(Point{ 18, 19 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 19, 19 }), StoneType::WHITE);

    bd.Play(Point{ 19, 18 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 19, 19 }), StoneType::NONE);
}

TEST_CASE("[Board] Capture Many at Corner Test")
{
    Board bd(19);

    // 11시 방향에서 테스트
    bd.Play(Point{ 1, 1 }, StoneType::BLACK);
    bd.Play(Point{ 2, 1 }, StoneType::BLACK);
    bd.Play(Point{ 1, 2 }, StoneType::BLACK);

    bd.Play(Point{ 1, 3 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 1, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 2, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 1, 2 }), StoneType::BLACK);

    bd.Play(Point{ 3, 1 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 1, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 2, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 1, 2 }), StoneType::BLACK);

    bd.Play(Point{ 2, 2 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 1, 1 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 2, 1 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 1, 2 }), StoneType::NONE);

    // 5시 방향에서 테스트
    bd.Play(Point{ 19, 19 }, StoneType::WHITE);
    bd.Play(Point{ 18, 19 }, StoneType::WHITE);
    bd.Play(Point{ 19, 18 }, StoneType::WHITE);

    bd.Play(Point{ 17, 19 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 19, 19 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 18, 19 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 19, 18 }), StoneType::WHITE);

    bd.Play(Point{ 19, 17 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 19, 19 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 18, 19 }), StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 19, 18 }), StoneType::WHITE);

    bd.Play(Point{ 18, 18 }, StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 19, 19 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 18, 19 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 19, 18 }), StoneType::NONE);
}

TEST_CASE("[Board] Capture One at Edge Test")
{
    Board bd(19);

    bd.Play(Point{ 10, 1 }, StoneType::BLACK);

    bd.Play(Point{ 9, 1 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::BLACK);

    bd.Play(Point{ 10, 2 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::BLACK);

    bd.Play(Point{ 11, 1 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::NONE);
}

TEST_CASE("[Board] Capture Many at Edge Test")
{
    Board bd(19);

    bd.Play(Point{ 9, 1 }, StoneType::BLACK);
    bd.Play(Point{ 10, 1 }, StoneType::BLACK);
    bd.Play(Point{ 11, 1 }, StoneType::BLACK);

    bd.Play(Point{ 8, 1 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 9, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 1 }), StoneType::BLACK);

    bd.Play(Point{ 12, 1 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 9, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 1 }), StoneType::BLACK);

    bd.Play(Point{ 9, 2 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 9, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 1 }), StoneType::BLACK);

    bd.Play(Point{ 10, 2 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 9, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::BLACK);
    CHECK_EQ(bd.At(Point{ 11, 1 }), StoneType::BLACK);

    bd.Play(Point{ 11, 2 }, StoneType::WHITE);
    CHECK_EQ(bd.At(Point{ 9, 1 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 10, 1 }), StoneType::NONE);
    CHECK_EQ(bd.At(Point{ 11, 1 }), StoneType::NONE);
}

TEST_CASE("[Board] Suicide Tests")
{
    Board bd(19);

    bd.Play(Point{ 9, 9 }, StoneType::BLACK);
    bd.Play(Point{ 9, 10 }, StoneType::BLACK);
    bd.Play(Point{ 9, 11 }, StoneType::BLACK);
    bd.Play(Point{ 10, 11 }, StoneType::BLACK);
    bd.Play(Point{ 11, 9 }, StoneType::BLACK);
    bd.Play(Point{ 11, 10 }, StoneType::BLACK);
    bd.Play(Point{ 11, 11 }, StoneType::BLACK);
    bd.Play(Point{ 10, 9 }, StoneType::BLACK);

    CHECK_EQ(bd.IsSuicide(Point{ 10, 10 }, StoneType::BLACK), false);
    CHECK_EQ(bd.IsSuicide(Point{ 10, 10 }, StoneType::WHITE), true);

    bd.Play(Point{ 8, 9 }, StoneType::WHITE);
    bd.Play(Point{ 8, 10 }, StoneType::WHITE);
    bd.Play(Point{ 8, 11 }, StoneType::WHITE);
    bd.Play(Point{ 12, 9 }, StoneType::WHITE);
    bd.Play(Point{ 12, 10 }, StoneType::WHITE);
    bd.Play(Point{ 12, 11 }, StoneType::WHITE);
    bd.Play(Point{ 9, 8 }, StoneType::WHITE);
    bd.Play(Point{ 10, 8 }, StoneType::WHITE);
    bd.Play(Point{ 11, 8 }, StoneType::WHITE);
    bd.Play(Point{ 9, 12 }, StoneType::WHITE);
    bd.Play(Point{ 10, 12 }, StoneType::WHITE);

    CHECK_EQ(bd.IsSuicide(Point{ 10, 10 }, StoneType::BLACK), false);
    CHECK_EQ(bd.IsSuicide(Point{ 10, 10 }, StoneType::WHITE), true);

    bd.Play(Point{ 11, 12 }, StoneType::WHITE);

    CHECK_EQ(bd.IsSuicide(Point{ 10, 10 }, StoneType::BLACK), true);
    CHECK_EQ(bd.IsSuicide(Point{ 10, 10 }, StoneType::WHITE), false);
}

TEST_CASE("[Board] Fake Ko Test")
{
    Board bd(19);

    bd.Play(Point{ 9, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 11 }, StoneType::BLACK);
    bd.Play(Point{ 11, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 9 }, StoneType::BLACK);

    bd.Play(Point{ 9, 11 }, StoneType::WHITE);
    bd.Play(Point{ 10, 12 }, StoneType::WHITE);
    bd.Play(Point{ 11, 11 }, StoneType::WHITE);
    bd.Play(Point{ 12, 10 }, StoneType::WHITE);
    bd.Play(Point{ 11, 9 }, StoneType::WHITE);

    bd.Play(Point{ 10, 10 }, StoneType::WHITE);

    CHECK_FALSE(bd.IsKo(Point{ 10, 11 }));
    CHECK_FALSE(bd.IsKo(Point{ 11, 10 }));
}

TEST_CASE("[Board] Ko Test")
{
    Board bd(19);

    bd.Play(Point{ 9, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 11 }, StoneType::BLACK);
    bd.Play(Point{ 11, 10 }, StoneType::BLACK);
    bd.Play(Point{ 10, 9 }, StoneType::BLACK);

    bd.Play(Point{ 9, 11 }, StoneType::WHITE);
    bd.Play(Point{ 10, 12 }, StoneType::WHITE);
    bd.Play(Point{ 11, 11 }, StoneType::WHITE);

    bd.Play(Point{ 10, 10 }, StoneType::WHITE);

    CHECK_EQ(bd.IsKo(Point{ 10, 11 }), true);

    bd.Play(Point{ 1, 1 });
    bd.Play(Point{ 1, 2 });

    CHECK_FALSE(bd.IsKo(Point{ 10, 11 }));
}

TEST_CASE("[Board] Ko at Corner Test")
{
    Board bd(19);

    bd.Play(Point{ 1, 2 });
    bd.Play(Point{ 1, 3 });
    bd.Play(Point{ 2, 1 });
    bd.Play(Point{ 2, 2 });

    bd.Play(Point{ 1, 1 }, StoneType::WHITE);

    CHECK_EQ(bd.IsKo(Point{ 1, 2 }), true);
}

TEST_CASE("[Board] Ko at Edge Test")
{
    Board bd(19);

    bd.Play(Point{ 8, 1 }, StoneType::BLACK);
    bd.Play(Point{ 9, 2 }, StoneType::BLACK);
    bd.Play(Point{ 10, 1 }, StoneType::BLACK);
    bd.Play(Point{ 10, 2 }, StoneType::WHITE);
    bd.Play(Point{ 11, 1 }, StoneType::WHITE);
    
    bd.Play(Point{ 9, 1 }, StoneType::WHITE);

    CHECK_EQ(bd.IsKo(Point{ 10, 1 }), true);
}
