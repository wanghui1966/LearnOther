#ifndef GAME_STATE_OVER_H
#define GAME_STATE_OVER_H

#include "GameState.h"

class GameStateOver : public GameState
{
public:
    explicit GameStateOver(MajiangRule *rule) { m_game_state = GAME_STATE_OVER; m_rule = rule; }
    virtual ~GameStateOver() {}

public:
    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

#endif
