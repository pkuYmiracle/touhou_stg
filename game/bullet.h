#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include <QObject>
#include "livingentity.h"

class Bullet : public Entity
{
    Q_OBJECT
    LivingEntity    *launcher;
    qreal           atk = 0;
public:
    explicit Bullet(LivingEntity *e);

    void setLauncher(LivingEntity *newLauncher);
    LivingEntity *getLauncher() const;
    qreal getAtk() const;
    void setAtk(qreal newAtk);
};

#endif // BULLET_H
