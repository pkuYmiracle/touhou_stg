#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "game/bulletgroup.h"
#include "game/livingentity.h"

class GameController;
class Player : public LivingEntity {
    GameController *gc;
    BulletGroup *bulletGroup;

public:
    explicit Player(GameController *gc, QString url);

    //  每frame调用一次
    //  功能：发射子弹，更新速度向量
    void advance(int phase) override;
    BulletGroup *getBulletGroup() const;
    void setBulletGroup(BulletGroup *newBulletGroup);
};

#endif  // PLAYER_H
