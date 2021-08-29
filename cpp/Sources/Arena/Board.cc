#include <Arena/Board.hpp>

#include <array>
#include <iomanip>

namespace
{
constexpr std::uint16_t shift(Arena::StoneType type)
{
    return 4 * static_cast<std::uint16_t>(type);
}
}  // namespace

namespace Arena
{
Board::Board(int boardSize)
    : boardSize_(boardSize), actualBoardSize_((boardSize + 2) * (boardSize + 2))
{
    board_.resize(actualBoardSize_);
    parent_.resize(actualBoardSize_);
    next_.resize(actualBoardSize_);
    liberties_.resize(actualBoardSize_);
    neighbors_.resize(actualBoardSize_);

    std::fill(begin(board_), end(board_), StoneType::INVALID);
    std::fill(begin(parent_), end(parent_), actualBoardSize_);
    std::fill(begin(next_), end(next_), actualBoardSize_);
    std::fill(begin(liberties_), end(liberties_), 0);
    std::fill(begin(neighbors_), end(neighbors_), 0);

    for (int y = 1; y <= boardSize; ++y)
    {
        for (int x = 1; x <= boardSize; ++x)
        {
            const int idx = IDX(x, y);

            board_[idx] = StoneType::NONE;

            const bool xEdge = (x == 1 || x == boardSize);
            const bool yEdge = (y == 1 || y == boardSize);

            neighbors_[idx] += ((1 + !xEdge) << shift(StoneType::NONE)) |
                               (xEdge << shift(StoneType::BLACK)) |
                               (xEdge << shift(StoneType::WHITE));
            neighbors_[idx] += ((1 + !yEdge) << shift(StoneType::NONE)) |
                               (yEdge << shift(StoneType::BLACK)) |
                               (yEdge << shift(StoneType::WHITE));
        }
    }
}

int Board::GetBoardSize() const
{
    return boardSize_;
}

bool Board::IsOnBoard(const Point& pt) const
{
    return (1 <= pt.X && pt.X <= boardSize_) &&
           (1 <= pt.Y && pt.Y <= boardSize_);
}

bool Board::IsValidMove(const Point& pt) const
{
    if (pt == Resign)
        return true;

    if (!IsOnBoard(pt) || (At(pt) != StoneType::NONE))
        return false;

    const int stonesIncEdge = countLine(IDX(pt), current_, true);
    const int stonesNotIncEdge = countLine(IDX(pt), current_, false);

    if (current_ == StoneType::WHITE && stonesNotIncEdge >= 7)
        return true;
    else if (current_ == StoneType::BLACK && stonesNotIncEdge == 7 &&
             stonesIncEdge == 7)
        return true;

    if (IsSuicide(pt) || IsKo(pt))
        return false;

    if (current_ == StoneType::WHITE)
        return true;

    return stonesIncEdge < 8;
}

bool Board::IsKo(const Point& pt) const
{
    if (ko_ == Resign)
        return false;

    return ko_ == pt;
}

bool Board::IsSuicide(const Point& pt, StoneType color) const
{
    if (color == StoneType::NONE)
        color = current_;

    if (countNeighbors(IDX(pt), StoneType::NONE) > 0)
        return false;

    for (NeighborIterator it(*this, pt); it; ++it)
    {
        const int neighborIdx = IDX(*it);
        const int libs = (parent_[neighborIdx] == actualBoardSize_)
                             ? 9999
                             : liberties_[parent_[neighborIdx]];

        if (board_[neighborIdx] == color && libs > 1)
            return false;

        if (board_[neighborIdx] == Opponent(color) && libs <= 1)
            return false;
    }

    return true;
}

StoneType Board::At(const Point& pt) const
{
    return board_[IDX(pt)];
}

bool Board::IsFinished() const
{
    return isFinished_;
}

StoneType Board::GetCurrentPlayer() const
{
    return current_;
}

StoneType Board::GetWinner() const
{
    return winner_;
}

void Board::Play(const Point& pt, StoneType color)
{
    if (isFinished_)
        return;

    if (color != StoneType::NONE)
        current_ = color;

    ko_ = Resign;

    if (pt == Resign || !IsValidMove(pt))
    {
        isFinished_ = true;
        winner_ = Opponent(current_);

        return;
    }

    const int idx = IDX(pt);

    board_[idx] = current_;
    next_[idx] = idx;
    parent_[idx] = idx;
    liberties_[idx] = countNeighbors(idx, StoneType::NONE);
    addNeighbors(idx, current_);

    int capturedSize = 0;
    int capturedIdx = 0;

    const bool koShape =
        neighbors_[idx] & (4 * (1 << shift(Opponent(current_))));

    for (NeighborIterator it(*this, pt); it; ++it)
    {
        const int neighborIdx = IDX(*it);

        if (board_[neighborIdx] == current_)
        {
            const int pt1 = parent_[idx];
            const int pt2 = parent_[neighborIdx];

            mergeGroup(pt1, pt2);
        }
        else if (board_[neighborIdx] == Opponent(current_))
        {
            if (liberties_[parent_[neighborIdx]] <= 0)
            {
                const int captured = removeGroup(neighborIdx);

                capturedSize += captured;
                capturedIdx = neighborIdx;
            }
        }
    }

    if (capturedSize == 1 && koShape)
    {
        ko_ = PT(capturedIdx);
    }

    if (countLine(idx, current_, current_ == StoneType::WHITE) >= 7)
    {
        isFinished_ = true;
        winner_ = current_;
    }

    current_ = Opponent(current_);
}

void Board::ToStream(std::ostream& os) const
{
    os << "   ";
    for (int i = 0; i < boardSize_; ++i)
    {
        os << static_cast<char>('A' + i) << ' ';
    }

    for (int y = 1; y <= boardSize_; ++y)
    {
        os << '\n' << std::setw(2) << y << ' ';

        for (int x = 1; x <= boardSize_; ++x)
        {
            switch (At(Point{ x, y }))
            {
                case StoneType::BLACK:
                    os << "B ";
                    break;
                case StoneType::WHITE:
                    os << "W ";
                    break;
                default:
                    os << "  ";
                    break;
            }
        }
    }

    os << "   " << ColorStr(current_) << " to play\n";
}

int Board::IDX(const Point& pt) const
{
    return IDX(pt.X, pt.Y);
}

int Board::IDX(int x, int y) const
{
    return x + y * (boardSize_ + 2);
}

Point Board::PT(int idx) const
{
    const int x = idx % (boardSize_ + 2);
    const int y = idx / (boardSize_ + 2);

    return { x, y };
}

int Board::countNeighbors(int idx, StoneType color) const
{
    return (neighbors_[idx] >> shift(color)) & 0xF;
}

void Board::addNeighbors(int idx, StoneType color)
{
    std::array<int, 4> nearParents;
    int count = 0;

    for (NeighborIterator it(*this, PT(idx)); it; ++it)
    {
        const int neighborIdx = IDX(*it);

        neighbors_[neighborIdx] += (1 << shift(color));
        neighbors_[neighborIdx] -= (1 << shift(StoneType::NONE));

        bool found = false;
        for (int i = 0; i < count; ++i)
        {
            if (nearParents[i] == parent_[neighborIdx])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            if (parent_[neighborIdx] != actualBoardSize_)
                --liberties_[parent_[neighborIdx]];

            nearParents[count++] = parent_[neighborIdx];
        }
    }
}

void Board::removeNeighbors(int idx, StoneType color)
{
    std::array<int, 4> nearParents;
    int count = 0;

    for (NeighborIterator it(*this, PT(idx)); it; ++it)
    {
        const int neighborIdx = IDX(*it);

        neighbors_[neighborIdx] -= (1 << shift(color));
        neighbors_[neighborIdx] += (1 << shift(StoneType::NONE));

        bool found = false;
        for (int i = 0; i < count; ++i)
        {
            if (nearParents[i] == parent_[neighborIdx])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            if (parent_[neighborIdx] != actualBoardSize_)
                --liberties_[parent_[neighborIdx]];

            nearParents[count++] = parent_[neighborIdx];
        }
    }
}

void Board::mergeGroup(int idx1, int idx2)
{
    int idx = idx2;

    do
    {
        for (NeighborIterator it(*this, PT(idx)); it; ++it)
        {
            if (board_[IDX(*it)] == StoneType::NONE)
            {
                bool found = false;
                for (NeighborIterator it2(*this, *it); it2; ++it2)
                {
                    if (parent_[IDX(*it2)] == idx1)
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    ++liberties_[idx1];
                }
            }
        }

        parent_[idx] = idx1;
        idx = next_[idx];
    } while (idx != idx2);

    std::swap(next_[idx2], next_[idx1]);
}

int Board::removeGroup(int idx)
{
    int pos = idx;

    int removed = 0;
    const StoneType color = board_[idx];

    do
    {
        board_[pos] = StoneType::NONE;
        parent_[pos] = (boardSize_ + 2) * (boardSize_ + 2);

        removeNeighbors(pos, color);

        ++removed;
        pos = next_[pos];
    } while (pos != idx);

    return removed;
}

int Board::countLine(int idx, StoneType color, bool includeEdge) const
{
    const int extendedSize = boardSize_ + 2;
    const std::array<int, 4> dirs = { +1 - extendedSize, +1, +1 + extendedSize,
                                      +extendedSize };

    int maxCount = 0;

    for (const int dir : dirs)
    {
        int count = 1;

        for (int i = 1; board_[idx + i * dir] == color; ++i)
        {
            if (!includeEdge && is1stOr2ndLine(idx + i * dir))
                break;

            ++count;
        }

        for (int i = 1; board_[idx - i * dir] == color; ++i)
        {
            if (!includeEdge && is1stOr2ndLine(idx - i * dir))
                break;

            ++count;
        }

        maxCount = std::max(count, maxCount);
    }

    return maxCount;
}

bool Board::is1stOr2ndLine(int idx) const
{
    const Point pt = PT(idx);

    return (pt.X <= 2 || pt.X >= boardSize_ - 1) ||
           (pt.Y <= 2 || pt.Y >= boardSize_ - 1);
}

Board::NeighborIterator::NeighborIterator(const Board& bd, Point pt)
    : bd_(bd), pt_(std::move(pt))
{
}

Board::NeighborIterator& Board::NeighborIterator::operator++()
{
    ++offset_;
    return *this;
}

Board::NeighborIterator& Board::NeighborIterator::operator--()
{
    --offset_;
    return *this;
}

Board::NeighborIterator::operator bool() const
{
    return (0 <= offset_) && (offset_ < 4);
}

Point Board::NeighborIterator::operator*() const
{
    const int extendedSize = bd_.boardSize_ + 2;
    const std::array<int, 4> dirs{ -1, +1, -extendedSize, +extendedSize };
    const int idx = bd_.IDX(pt_) + dirs[offset_];

    return bd_.PT(idx);
}
}  // namespace Arena
