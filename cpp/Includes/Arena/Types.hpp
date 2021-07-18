#ifndef ARENA_TYPES_HPP
#define ARENA_TYPES_HPP

namespace Arena
{
//!
//! \brief 착수 위치를 표현하는 구조체.
//! X, Y는 각각 0에서 18 사이의 숫자를 가질 수 있습니다.
//!
struct Point final
{
    int X, Y;
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
