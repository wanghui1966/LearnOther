#include "GameStateChoosePiao.h"
#include "../MajiangRule.h"

void GameStateChoosePiao::Enter()
{   
    std::cout << "GameStateChoosePiao::Enter" << std::endl;
}   

void GameStateChoosePiao::Execute()
{
    ++m_choose_piao_num;
    std::cout << "GameStateChoosePiao::Execute" << std::endl;
    if (CanEnterNextState())
    {
        m_rule->EnterGameState(GAME_STATE_OVER);
    }
}   

void GameStateChoosePiao::Exit()
{
    std::cout << "GameStateChoosePiao::Exit" << std::endl;
}

bool GameStateChoosePiao::CanEnterNextState()
{
    return (m_choose_piao_num == 4);
}
