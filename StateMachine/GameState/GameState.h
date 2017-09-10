#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>

enum
{
    GAME_STATE_NONE = 0,
    GAME_STATE_START,
    GAME_STATE_CHOOSE_PIAO,
    GAME_STATE_SHUFFLE,
    GAME_STATE_DEAL_HAND_MJ,
    GAME_STATE_GAMING,
    GAME_STATE_BALANCE,
    GAME_STATE_OVER,
    GAME_STATE_END,
};

class MajiangRule;
class GameState
{
public:
    GameState() {}
    virtual ~GameState() {}

public:
    int GetGameState() { return m_game_state; }

public:
    virtual void Enter() = 0;
    virtual void Execute() = 0;
    virtual void Exit() = 0;

protected:
    int                     m_game_state = GAME_STATE_NONE;
    MajiangRule             *m_rule = nullptr;
};

#endif
