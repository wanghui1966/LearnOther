#ifndef GAME_STATE_CHOOSE_PIAO_H
#define GAME_STATE_CHOOSE_PIAO_H

#include "GameState.h"

class GameStateChoosePiao : public GameState
{
public:
    explicit GameStateChoosePiao(MajiangRule *rule) { m_game_state = GAME_STATE_CHOOSE_PIAO; m_rule = rule; }
    virtual ~GameStateChoosePiao() {}

public:
    virtual void Enter();
    virtual void Execute();
    virtual void Exit();

protected:
    virtual bool CanEnterNextState();

protected:
    // 测试，选漂人数
    int m_choose_piao_num = 0;
};

#endif
