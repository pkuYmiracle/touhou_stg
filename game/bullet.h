#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include <QObject>

class Bullet : public Entity
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent);
};

#endif // BULLET_H
