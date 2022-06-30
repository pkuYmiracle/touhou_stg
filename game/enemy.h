#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>

#include "livingentity.h"

class EnemyPrototype;
class Enemy : public LivingEntity {
    Q_OBJECT
    explicit Enemy();
    friend class EnemyPrototype;
};

#endif  // ENEMY_H
