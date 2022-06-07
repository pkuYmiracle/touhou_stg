#include "bullet.h"
#include "bulletprototype.h"
#include <QGraphicsScene>

BulletPrototype::BulletPrototype(QVector2D _delta, QVector2D _speed, QString _picUrl)
    : delta(_delta), speed(_speed), picUrl(_picUrl)
{

}

Bullet* BulletPrototype::spawnBulletFrom(LivingEntity *e) const
{
    Bullet *b = new Bullet(e);
    b->setPos(e->pos() + delta.toPointF());
    b->setSpeed(speed);
    b->setPixmap(QPixmap(picUrl));
    e->scene()->addItem(b);
    return b;
}
