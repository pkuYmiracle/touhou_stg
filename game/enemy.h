#ifndef ENEMY_H
#define ENEMY_H

#include "livingentity.h"
#include <QObject>

class EnemyPrototype;
class Enemy : public LivingEntity
{
    Q_OBJECT
    explicit Enemy();
    friend class EnemyPrototype;
};

#endif // ENEMY_H
