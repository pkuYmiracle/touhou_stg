#ifndef BULLET_H
#define BULLET_H

#include <QObject>

#include "entity.h"
#include "livingentity.h"

// bullet暂时没有朝向
class Bullet : public Entity {
    Q_OBJECT
    LivingEntity *launcher;

    ///
    /// \brief atk 该子弹的攻击力
    ///
    qreal atk = 0;

public:
    explicit Bullet(LivingEntity *e);
    ///
    /// \brief setLauncher
    /// \param newLauncher
    /// 设置发射者。在碰撞检测与血量计算中会使用该参数。
    ///
    void setLauncher(LivingEntity *newLauncher);
    LivingEntity *getLauncher() const;

    qreal getAtk() const;
    void setAtk(qreal newAtk);
};

#endif  // BULLET_H
