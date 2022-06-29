#include "bullet.h"
#include "enemy.h"
#include "entity.h"
#include "qgraphicsitem.h"
#include <QGraphicsScene>
#include "game/player.h"
#include "game/config.h"
#include <QDebug>
#include <assert.h>
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

void Entity::setPixmap(const QPixmap &pixmap) {
    this->QGraphicsPixmapItem::setPixmap(pixmap);
    this->setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
}

Entity::Entity()
{

}

void Entity::advance(int phase)
{
    if (phase == 1) return;
    if (scene() == 0) return;

    if (this->isPlayer()) {
        //Player要完整在框内.
        this->setPos(this->x(), this->y() + getSpeed().y());
        if (GAME_BOARD_RECT.contains(this->mapRectToScene(this->boundingRect())) == false) {
            this->setPos(this->x(), this->y() - getSpeed().y());
        }

        this->setPos(this->x() + getSpeed().x(), this->y());
        if (GAME_BOARD_RECT.contains(this->mapRectToScene(this->boundingRect())) == false) {
            this->setPos(this->x() - getSpeed().x(), this->y());
        }
    } else {
            this->setPos(getSpeed().toPointF() + this->pos());
            if (GAME_BOARD_RECT.adjusted(-HIDEN_EDGE, -HIDEN_EDGE, HIDEN_EDGE, HIDEN_EDGE).intersects(
                        this->mapRectToScene(this->boundingRect())) == false) {
                scene()->removeItem(this);
                this->deleteLater();
            }
//        }
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
