#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "game/bulletgroup.h"
#include "game/livingentity.h"

class GameController;
class Player : public LivingEntity {
    GameController *gc;

    ///
    /// \brief bulletGroup 所发射的弹幕群
    ///
    BulletGroup *bulletGroup;

public:
    explicit Player(GameController *gc, QString url);

    ///
    /// \brief advance 逐帧调用，处理玩家输入
    /// \param phase
    ///
    void advance(int phase) override;

    BulletGroup *getBulletGroup() const;
    void setBulletGroup(BulletGroup *newBulletGroup);
};

#endif  // PLAYER_H
