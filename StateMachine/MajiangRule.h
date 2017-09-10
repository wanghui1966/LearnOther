#ifndef MAJIANG_RULE_H
#define MAJIANG_RULE_H

#include <map>

#include "GameState/GameState.h"
#include "GameState/GameStateStart.h"
#include "GameState/GameStateChoosePiao.h"
#include "GameState/GameStateOver.h"
#include "GameState/GameStateEnd.h"

class GameState;
class GameStateStart;
class GameStateChoosePiao;
class GameStateOver;
class GameStateEnd;
class MajiangRule
{
public:
    MajiangRule();
    virtual ~MajiangRule();

public:
    // 初始化状态机
    void Init();

    // 进入下一个状态
    void EnterGameState(int next_game_state);

public:
    // 转发上层来的状态执行
    void HandleExecute(int game_state);

protected:
    GameState                           *m_cur_game_state;          // 当前游戏状态
    std::map<int, GameState*>           m_game_state_map;           // 所有状态机
};

#endif
