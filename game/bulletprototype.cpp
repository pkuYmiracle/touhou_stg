#include "bullet.h"
#include "bulletprototype.h"
#include <QGraphicsScene>

BulletPrototype::BulletPrototype(QVector2D _delta, QVector2D _speed)
    : delta(_delta), speed(_speed)
{

}

void BulletPrototype::spawnBulletFrom(LivingEntity *e) const
{
    Bullet *b = new Bullet(e);
    b->setPos(e->pos() + delta.toPointF());
    b->setSpeed(speed);
    e->scene()->addItem(b);
}
