#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include <QObject>
#include "livingentity.h"

class Bullet : public Entity
{
    Q_OBJECT
    LivingEntity    *launcher;
public:
    explicit Bullet();
};

#endif // BULLET_H
