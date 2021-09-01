#ifndef ARENA_AGENT_HPP
#define ARENA_AGENT_HPP

#include <Arena/Types.hpp>

#include <string>

namespace Arena
{
//!
//! \brief ������Ʈ�� ���� �� Agent Ŭ������ ��ӹ޾� ���弼��.
//! ����: �α׸� "����" stdout(cout)�� ������ ������.
//!
class Agent
{
 public:
    //! ������
    //! \param name ������Ʈ�� �̸�.
    Agent(std::string name);

    //! �⺻ �Ҹ���
    virtual ~Agent() noexcept = default;

    //! �����κ��� ���� ũ�⸦ �޾��� �� ȣ��˴ϴ�.
    //! \param boardSize ���� �� ��.
    virtual void BoardSize(int boardSize) = 0;

    //! �������� ���� ���� ��û�޾��� �� ȣ��˴ϴ�.
    //! \param color ������ ���� ����.
    //! \return ������ ���� ��ġ.
    virtual Point GenMove(StoneType color) = 0;

    //! ������ ��ġ�� ���� ������ �޾��� �� ȣ��˴ϴ�.
    //! \param color ������ �� ����.
    //! \param pt ���� ��ġ.
    virtual void Play(StoneType color, const Point& pt) = 0;

    //! ��/�� ���ڿ��� ���� �ð� ������ �޾��� �� ȣ��˴ϴ�.
    //! \param blackTime �濡�� ���� �ð�(��)
    //! \param whiteTime �鿡�� ���� �ð�(��)
    virtual void TimeLeft(int blackTime, int whiteTime) = 0;

    //! �����κ��� ���� �ʱ�ȭ ����� ������ ȣ��˴ϴ�.
    virtual void ClearBoard() = 0;

    //! ������Ʈ�� �����մϴ�.
    void Run();

 private:
    StoneType parseStoneType(const std::string& token) const;

 private:
    std::string name_;
};
}  // namespace Arena

#endif  // ARENA_AGENT_HPP
