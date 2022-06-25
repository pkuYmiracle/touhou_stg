#ifndef BULLETPROTOTYPE_H
#define BULLETPROTOTYPE_H

#include "game/config.h"
#include "game/livingentity.h"
#include "bullet.h"
#include "qdebug.h"
#include "qvector2d.h"

class BulletPrototype
{
    QVector2D   delta;
    QVector2D   speed;
    qreal       atk;
    QString     picUrl;
public:
    explicit BulletPrototype(QVector2D _delta, QVector2D _speed, qreal atk = DEFAULT_ATK, QString _picUrl = ":/game/assets/bullet.png");

    Bullet*  spawnBulletFrom(LivingEntity *e) const;
};

#endif // BULLETPROTOTYPE_H
