#include "bullet.h"
#include "enemy.h"
#include "entity.h"
#include "qgraphicsitem.h"
#include <QGraphicsScene>
#include "game/player.h"
#include <QDebug>

QVector2D Entity::getSpeed() const
{
    return speed;
}

void Entity::setSpeed(QVector2D newSpeed)
{
    speed = newSpeed;
}

Entity::Entity()
{

}

void Entity::advance(int phase)
{
    if (phase == 1) return;
    this->setPos(getSpeed().toPointF() + this->pos());
    if (this->isPlayer()) {
        //Player要完整在框内.
        if (scene()->sceneRect().contains(this->mapRectToScene(this->boundingRect())) == false) {
            this->setPos(this->pos() - getSpeed().toPoint()); //撤销.
        }
    } else {
        //东西可以飞出去.
        if (scene()->sceneRect().intersects(this->mapRectToScene(this->boundingRect())) == false) {
            scene()->removeItem(this);
        }
    }
}

bool Entity::isPlayer() const
{
    return dynamic_cast<const Player*>(this) != 0;
}

bool Entity::isEnemy() const
{
    return dynamic_cast<const Enemy*>(this) != 0;
}

bool Entity::isBullet() const
{
    return dynamic_cast<const Bullet*>(this) != 0;
}
