#ifndef ARENA_TYPES_HPP
#define ARENA_TYPES_HPP

namespace Arena
{
//!
//! \brief ���� ��ġ�� ǥ���ϴ� ����ü.
//! X, Y�� ���� 1���� 19 ������ ���ڸ� ���� �� �ֽ��ϴ�.
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

//! ����� ǥ���ϴ� ��ǥ.
inline const Point Resign{ -1, -1 };

//!
//! \brief ���� ���� ǥ���ϴ� ����ü.
//!
enum class StoneType
{
    NONE,
    BLACK,
    WHITE,
    INVALID
};

//! ������ ���� ��ȯ�ϴ� �Լ�.
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
