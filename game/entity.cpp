#include "bullet.h"
#include "enemy.h"
#include "entity.h"
#include "qgraphicsitem.h"
#include <QGraphicsScene>
#include "game/player.h"
#include <QDebug>
#include <assert.h>
#include "config.h"

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
    if (scene() == 0) return;

    this->setPos(getSpeed().toPointF() + this->pos());
    qDebug() << "remove" << endl;
    if (this->isPlayer()) {
        //Player要完整在框内.
        if (scene()->sceneRect().contains(this->mapRectToScene(this->boundingRect())) == false) {
            this->setPos(this->pos() - getSpeed().toPoint()); //撤销.
        }
    } else {
//        qDebug() << scene()->sceneRect().adjusted(-HIDEN_EDGE, -HIDEN_EDGE, HIDEN_EDGE, HIDEN_EDGE) << endl;
        if (scene()->sceneRect().adjusted(-HIDEN_EDGE, -HIDEN_EDGE, HIDEN_EDGE, HIDEN_EDGE).intersects(
                    this->mapRectToScene(this->boundingRect())) == false) {
            scene()->removeItem(this);
//            this->deleteLater();
        }
    }
    qDebug() << 1 << endl;
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
