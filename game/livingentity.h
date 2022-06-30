#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include <QObject>

#include "game/entity.h"

class LivingEntity : public Entity {
    qreal hp;  // short for health point

public:
    explicit LivingEntity();
    ///
    /// \brief advance 逐帧调用，碰撞检测与血量计算
    /// \param phase
    ///
    void advance(int phase) override;

    float getHp() const;
    void setHp(qreal newHp);
};

#endif  // LIVINGENTITY_H
