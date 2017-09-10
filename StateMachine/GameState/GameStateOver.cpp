#include "GameStateOver.h"
#include "../MajiangRule.h"

void GameStateOver::Enter()
{   
    std::cout << "GameStateOver::Enter" << std::endl;
}   

void GameStateOver::Execute()
{   
    std::cout << "GameStateOver::Execute" << std::endl;
    m_rule->EnterGameState(GAME_STATE_END);
}   

void GameStateOver::Exit()
{
    std::cout << "GameStateOver::Exit" << std::endl;
} 
