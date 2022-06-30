#ifndef BULLET_H
#define BULLET_H

#include <QObject>

#include "entity.h"
#include "livingentity.h"

// bullet暂时没有朝向
class Bullet : public Entity {
    Q_OBJECT
    LivingEntity *launcher;
    qreal atk = 0;

public:
    explicit Bullet(LivingEntity *e);

    void setLauncher(LivingEntity *newLauncher);
    LivingEntity *getLauncher() const;
    qreal getAtk() const;
    void setAtk(qreal newAtk);
};

#endif  // BULLET_H
