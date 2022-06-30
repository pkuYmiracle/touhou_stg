#include "game_board.h"

#include <QString>

#include "baseboard.h"
#include "game/gamecontroller.h"
#include "mypushbottom.h"
Game_board::Game_board(QWidget *parent, const std::vector<QString> &pos)
    : Baseboard{parent},
      gc{new GameController(pos)} {  // id :关卡编号，pos:人物图片url
}
