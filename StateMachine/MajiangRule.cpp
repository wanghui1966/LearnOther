#include "MajiangRule.h"
#include "GameState/GameState.h"
#include "GameState/GameStateStart.h"
#include "GameState/GameStateChoosePiao.h"
#include "GameState/GameStateOver.h"
#include "GameState/GameStateEnd.h"

MajiangRule::MajiangRule()
: m_cur_game_state(nullptr)
{

}

MajiangRule::~MajiangRule()
{
    for (std::map<int, GameState*>::iterator it = m_game_state_map.begin(); it != m_game_state_map.end(); ++it)
    {
        delete it->second;
        it->second = nullptr;
    }
    m_game_state_map.clear();
}

void MajiangRule::Init()
{
    m_game_state_map.insert(std::pair<int, GameState*>(GAME_STATE_START, new GameStateStart(this)));
    m_game_state_map.insert(std::pair<int, GameState*>(GAME_STATE_CHOOSE_PIAO, new GameStateChoosePiao(this)));
    m_game_state_map.insert(std::pair<int, GameState*>(GAME_STATE_OVER, new GameStateOver(this)));
    m_game_state_map.insert(std::pair<int, GameState*>(GAME_STATE_END, new GameStateEnd(this)));

    EnterGameState(GAME_STATE_START);
}

void MajiangRule::EnterGameState(int next_game_state)
{
    auto it = m_game_state_map.find(next_game_state);
    if (it == m_game_state_map.end())
    {
        return;
    }
    if (it->second == nullptr)
    {
        return;
    }
    if (m_cur_game_state != nullptr)
    {
        m_cur_game_state->Exit();
    }
    if (next_game_state == GAME_STATE_END)
    {
        std::cout << "end" << std::endl;
        return;
    }

    m_cur_game_state = it->second;
    m_cur_game_state->Enter();
}

void MajiangRule::HandleExecute(int game_state)
{
    if (m_cur_game_state == nullptr || m_cur_game_state->GetGameState() != game_state)
    {
        std::cout << "MajiangRule::HandleExecute error" << std::endl;
        return;
    }

    m_cur_game_state->Execute();
}
