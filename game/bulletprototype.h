#ifndef BULLETPROTOTYPE_H
#define BULLETPROTOTYPE_H

#include "game/livingentity.h"
#include "qvector2d.h"

class BulletPrototype
{
    QVector2D delta;
    QVector2D speed;
public:
    explicit BulletPrototype(QVector2D _delta, QVector2D _speed);
    void spawnBulletFrom(LivingEntity *e) const;
};

#endif // BULLETPROTOTYPE_H
