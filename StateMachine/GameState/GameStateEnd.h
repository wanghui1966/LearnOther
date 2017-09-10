#ifndef GAME_STATE_END_H
#define GAME_STATE_END_H

#include "GameState.h"

class GameStateEnd : public GameState
{
public:
    explicit GameStateEnd(MajiangRule *rule) { m_game_state = GAME_STATE_END; m_rule = rule; }
    virtual ~GameStateEnd() {}

public:
    virtual void Enter() {}
    virtual void Execute() {}
    virtual void Exit() {}
};

#endif
