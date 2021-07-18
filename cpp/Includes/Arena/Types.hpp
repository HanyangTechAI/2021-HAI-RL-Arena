#ifndef ARENA_TYPES_HPP
#define ARENA_TYPES_HPP

namespace Arena
{
//!
//! \brief 착수 위치를 표현하는 구조체.
//! X, Y는 각각 1에서 19 사이의 숫자를 가질 수 있습니다.
//!
struct Point final
{
    int X, Y;

    bool operator==(const Point& pt) const
    {
        return (X == pt.X) && (Y == pt.Y);
    }

    bool operator!=(const Point& pt) const
    {
        return !(*this == pt);
    }
};

//! 기권을 표시하는 좌표.
inline const Point Resign{ -1, -1 };

//!
//! \brief 돌의 색을 표현하는 열거체.
//!
enum class StoneType
{
    NONE,
    BLACK,
    WHITE,
    INVALID
};

//! 상대방의 색을 반환하는 함수.
constexpr StoneType Opponent(StoneType color)
{
    switch (color)
    {
        case StoneType::BLACK:
            return StoneType::WHITE;

        case StoneType::WHITE:
            return StoneType::BLACK;

        default:
            return StoneType::INVALID;
    }
}
}  // namespace Arena

#endif  // ARENA_TYPES_HPP
