#ifndef BULLETPROTOTYPE_H
#define BULLETPROTOTYPE_H

#include "game/config.h"
#include "game/livingentity.h"
#include "bullet.h"
#include "qvector2d.h"

class BulletPrototype
{
    QVector2D   delta;
    QVector2D   speed;
    QString     picUrl;
    qreal       atk;
public:
    explicit BulletPrototype(QVector2D _delta, QVector2D _speed, qreal atk = DEFAULT_ATK, QString _picUrl = ":/game/assets/bullet.png");
    Bullet*     spawnBulletFrom(LivingEntity *e) const;
};

#endif // BULLETPROTOTYPE_H
