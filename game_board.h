#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <QString>

#include "baseboard.h"
#include "game/gamecontroller.h"
class Game_board : public Baseboard {
    Q_OBJECT
private:
    QString load_path;
    int id;
    GameController *gc;

public:
    explicit Game_board(QWidget *parent = nullptr,
                        const std::vector<QString> &pos = {});

signals:
};

#endif  // GAME_BOARD_H
