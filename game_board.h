#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "baseboard.h"
#include<QString>
class Game_board : public Baseboard
{
    Q_OBJECT
private:
    QString load_path;
    int id;
public:
    explicit Game_board(QWidget *parent = nullptr,int _id = 0,QString pos = "");

signals:

};

#endif // GAME_BOARD_H
