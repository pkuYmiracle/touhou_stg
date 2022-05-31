#ifndef ENEMY_H
#define ENEMY_H

#include "livingentity.h"
#include <QObject>

class Enemy : public LivingEntity
{
    Q_OBJECT
public:
    explicit Enemy(QObject *parent);
};

#endif // ENEMY_H
