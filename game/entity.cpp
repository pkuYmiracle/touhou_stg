#include "entity.h"
#include "qgraphicsitem.h"


QPointF Entity::getSpeed() const
{
    return speed;
}

void Entity::setSpeed(QPointF newSpeed)
{
    speed = newSpeed;
}

Entity::Entity()
{

}

void Entity::advance(int phase) {
    if (phase == 1) return;
    this->setPos(this->pos() + getSpeed());
}
