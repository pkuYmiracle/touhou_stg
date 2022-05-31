#ifndef ENEMY_H
#define ENEMY_H

#include "livingentity.h"
#include <QObject>

class Enemy : public LivingEntity
{
    Q_OBJECT
public:
    explicit Enemy();
};

#endif // ENEMY_H
