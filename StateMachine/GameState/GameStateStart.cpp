#include "GameStateStart.h"
#include "../MajiangRule.h"

void GameStateStart::Enter()
{   
    std::cout << "GameStateStart::Enter" << std::endl;
}   

void GameStateStart::Execute()
{   
    std::cout << "GameStateStart::Execute" << std::endl;
    m_rule->EnterGameState(GAME_STATE_CHOOSE_PIAO);
}   

void GameStateStart::Exit()
{
    std::cout << "GameStateStart::Exit" << std::endl;
} 
