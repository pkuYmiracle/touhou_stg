#ifndef PLAYER_H
#define PLAYER_H

#include "game/livingentity.h"
#include <QObject>

class Player : public LivingEntity
{
public:
    explicit Player();

//    每frame调用一次
//    功能：发射子弹，更新速度向量
//    void advance(int phase) override;

};

#endif // PLAYER_H
