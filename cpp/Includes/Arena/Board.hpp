#ifndef ARENA_BOARD_HPP
#define ARENA_BOARD_HPP

#include <Arena/Types.hpp>

#include <cstdint>
#include <vector>

namespace Arena
{
//!
//! \brief 게임 보드판 클래스.
//!
class Board final
{
 public:
    //! 생성자
    //! \param boardSize 바둑판의 크기.
    Board(int boardSize);

    //! 기본 복사 생성자
    Board(const Board&) = default;

    //! 기본 이동 생성자
    Board(Board&&) = default;

    //! 기본 복사 할당자
    Board& operator=(const Board&) = default;

    //! 기본 이동 할당자
    Board& operator=(Board&&) = default;

    //! 바둑판의 크기를 반환합니다.
    int GetBoardSize() const;

    //! 해당 착수점이 바둑판 안에 있는지 체크하는 메소드.
    //! \param pt 조사할 착수점 위치.
    //! \return 바둑판 안에 있으면 true, 밖에 있으면 false를 반환.
    bool IsOnBoard(const Point& pt) const;

    //! 해당 착수점이 유효한지를 체크하는 메소드.
    //! \param pt 조사할 착수점 위치.
    //! \return 유효하면 true, 유효하지 않으면 false를 반환.
    bool IsValidMove(const Point& pt) const;

    //! 해당 착수점이 유효하지 않은 패인지 체크하는 메소드.
    //! \param pt 조사할 착수점 위치.
    //! \return 유효하지 않은 패이면 true, 그렇지 않으면 false를 반환.
    bool IsKo(const Point& pt) const;

    //! 해당 착수점이 자살수인지 체크하는 메소드.
    //! \param pt 조사할 착수점 위치.
    //! \return 자살수이면 true, 그렇지 않으면 false를 반환.
    bool IsSuicide(const Point& pt) const;

    //! 해당 위치의 돌의 색깔을 반환합니다.
    //! \param pt 조사할 위치.
    //! \return 해당 위치의 돌의 색깔.
    StoneType At(const Point& pt) const;

    //! 게임이 종료되었는지 여부를 반환합니다.
    bool IsFinished() const;

    //! 현재 둘 차례인 색을 반환합니다.
    StoneType GetCurrentPlayer() const;

    //! 승자를 반환합니다.
    StoneType GetWinner() const;

    //! 착수합니다.
    //! \param pt 착수점 위치
    //! \param color 착수할 돌의 색깔 (기본값으로 둘 경우 current_로 설정됨)
    void Play(const Point& pt, StoneType color = StoneType::NONE);

 public:
    //!
    //! \brief 이웃한 위치를 순회하는 이터레이터
    //!
    class NeighborIterator final
    {
     public:
        NeighborIterator(const Board& bd, Point pt);

        NeighborIterator& operator++();
        NeighborIterator& operator--();

        operator bool() const;
        Point operator*() const;

     private:
        const Board& bd_;
        Point pt_;
        int offset_{ 0 };
    };

 private:
    int IDX(const Point& pt) const;
    int IDX(int x, int y) const;
    Point PT(int idx) const;

    int countNeighbors(int idx, StoneType color) const;
    void addNeighbors(int idx, StoneType color);
    void removeNeighbors(int idx, StoneType color);
    void mergeGroup(int idx1, int idx2);
    int removeGroup(int idx);

    int countLine(int idx, StoneType color, bool includeEdge) const;
    bool is1stOr2ndLine(int idx) const;

 private:
    int boardSize_;
    Point ko_{ Resign };
    StoneType current_{ StoneType::BLACK };
    StoneType winner_{ StoneType::INVALID };
    bool isFinished_{ false };

    std::vector<StoneType> board_;
    std::vector<int> parent_;
    std::vector<int> next_;
    std::vector<int> liberties_;
    std::vector<std::uint16_t> neighbors_;
};
}  // namespace Arena

#endif  // ARENA_BOARD_HPP
