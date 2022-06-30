#ifndef BULLETPROTOTYPE_H
#define BULLETPROTOTYPE_H

#include "bullet.h"
#include "game/config.h"
#include "game/livingentity.h"
#include "qdebug.h"
#include "qvector2d.h"

class BulletPrototype {

    ///
    /// \brief delta 发射点相对发射实体的偏移量
    ///
    QVector2D delta;

    ///
    /// \brief speed 子弹飞行速度
    ///
    QVector2D speed;

    ///
    /// \brief atk 子弹攻击力
    ///
    qreal atk;

    ///
    /// \brief picUrl 子弹素材url
    ///
    QString picUrl;

public:
    explicit BulletPrototype(QVector2D _delta, QVector2D _speed,
                             qreal atk = DEFAULT_ATK,
                             QString _picUrl = ":/game/assets/bullet.png");

    ///
    /// \brief spawnBulletFrom 从实体e处实例化该子弹原型并发射
    /// \param e
    /// \return 指向实例化Bullet的指针
    ///
    Bullet* spawnBulletFrom(LivingEntity* e) const;
};

#endif  // BULLETPROTOTYPE_H
