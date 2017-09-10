#ifndef GAME_STATE_START_H
#define GAME_STATE_START_H

#include "GameState.h"

class GameStateStart : public GameState
{
public:
    explicit GameStateStart(MajiangRule *rule) { m_game_state = GAME_STATE_START; m_rule = rule; }
    virtual ~GameStateStart() {}

public:
    virtual void Enter();
    virtual void Execute();
    virtual void Exit();
};

#endif
