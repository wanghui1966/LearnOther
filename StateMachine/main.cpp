#include "MajiangRule.h"

int main()
{
    MajiangRule *rule = new MajiangRule;
    rule->Init();

    rule->HandleExecute(GAME_STATE_START);

    rule->HandleExecute(GAME_STATE_CHOOSE_PIAO);
    rule->HandleExecute(GAME_STATE_CHOOSE_PIAO);
    rule->HandleExecute(GAME_STATE_CHOOSE_PIAO);
    rule->HandleExecute(GAME_STATE_CHOOSE_PIAO);

    rule->HandleExecute(GAME_STATE_OVER);

    return 0;
}
