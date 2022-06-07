#ifndef BULLETPROTOTYPE_H
#define BULLETPROTOTYPE_H

#include "game/livingentity.h"
#include "bullet.h"
#include "qvector2d.h"

class BulletPrototype
{
    QVector2D   delta;
    QVector2D   speed;
    QString     picUrl;
public:
    explicit BulletPrototype(QVector2D _delta, QVector2D _speed, QString _picUrl = ":/game/assets/bullet.png");
    Bullet*     spawnBulletFrom(LivingEntity *e) const;
};

#endif // BULLETPROTOTYPE_H
