#include "entity.h"
#include "qgraphicsitem.h"
#include <QGraphicsScene>
#include "game/player.h"
#include <QDebug>

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

void Entity::advance(int phase)
{
    if (phase == 1) return;
    this->setPos(this->pos() + getSpeed());
    if (scene()->sceneRect().contains(this->pos()) == false) {
        qDebug() << typeid(this).name() << endl;
        if (dynamic_cast<Player*>(this)) {
            this->setPos(this->pos() - getSpeed()); //撤销.
        } else {
            scene()->removeItem(this);
        }
    }
}
