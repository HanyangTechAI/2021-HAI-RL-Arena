#ifndef ARENA_AGENT_HPP
#define ARENA_AGENT_HPP

#include <Arena/Types.hpp>

#include <string>

namespace Arena
{
//!
//! \brief 에이전트를 만들 때 Agent 클래스를 상속받아 만드세요.
//! 주의: 로그를 "절대" stdout(cout)에 남기지 마세요.
//!
class Agent
{
 public:
    //! 생성자
    //! \param name 에이전트의 이름.
    Agent(std::string name);

    //! 기본 소멸자
    virtual ~Agent() noexcept = default;

    //! 서버로부터 판의 크기를 받았을 때 호출됩니다.
    //! \param boardSize 판의 줄 수.
    virtual void BoardSize(int boardSize) = 0;

    //! 서버가 시간 설정을 알려줄 때 호출됩니다.
    //! \param timesPerMove 한 턴당 주어진 시간.
    virtual void TimeSetting(int timesPerMove) = 0;

    //! 서버에게 다음 수를 요청받았을 때 호출됩니다.
    //! \param color 착수할 돌의 색깔.
    //! \return 생성된 착수 위치.
    virtual Point GenMove(StoneType color) = 0;

    //! 상대방이 착수한 위치와 상대방의 색깔 정보를 받았을 때 호출됩니다.
    //! \param oppColor 상대방의 돌 색깔.
    //! \param pt 상대방의 착수 위치.
    virtual void Play(StoneType oppColor, Point pt) = 0;

    //! 서버로부터 판의 초기화 명령이 들어오면 호출됩니다.
    virtual void ClearBoard() = 0;

    //! 에이전트를 가동합니다.
    void Run();

 private:
    StoneType parseStoneType(const std::string& token) const;

 private:
    std::string name_;
};
}  // namespace Arena

#endif  // ARENA_AGENT_HPP
