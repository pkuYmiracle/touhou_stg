#include "game_board.h"
#include "baseboard.h"
#include <QString>
#include "mypushbottom.h"
#include "game/gamecontroller.h"
Game_board::Game_board(QWidget *parent,const std::vector<QString> & pos)
    : Baseboard{parent},gc{new GameController (pos)}
{// id :关卡编号，pos:人物图片url


}
