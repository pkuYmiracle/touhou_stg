#include "game_board.h"
#include "baseboard.h"
#include <QString>
#include "mypushbottom.h"
Game_board::Game_board(QWidget *parent,int _id,QString pos)
    : Baseboard{parent},id(_id),load_path(pos)
{

    Mypushbottom * character_postion = new Mypushbottom(this,false,load_path,150);

    character_postion->resize(300,400);
    character_postion->move(100 ,this->height() - character_postion->height());
    character_postion->show();


}
