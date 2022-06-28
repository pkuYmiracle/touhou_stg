#ifndef PLAYER_H
#define PLAYER_H

#include "game/livingentity.h"
#include <QObject>

class GameController;
class Player : public LivingEntity
{
    GameController *gc;
public:

    explicit Player(GameController *gc,QString url);

//  每frame调用一次
//  功能：发射子弹，更新速度向量
    void advance(int phase) override;
};

#endif // PLAYER_H
