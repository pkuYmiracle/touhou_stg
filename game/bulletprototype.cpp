#include "bullet.h"
#include "bulletprototype.h"
#include <QGraphicsScene>

BulletPrototype::BulletPrototype(QVector2D _delta, QVector2D _speed, qreal atk, QString _picUrl)
    : delta(_delta), speed(_speed), atk(atk), picUrl(_picUrl)
{

}

Bullet* BulletPrototype::spawnBulletFrom(LivingEntity *e) const
{
    Bullet *b = new Bullet(e);
    b->setAtk(atk);
//    qDebug() << e->pos() + QPointF{e->boundingRect().width() / 2, e->boundingRect().height() / 2} << endl;
//    qDebug() << e->pos() << endl;

    b->setPos(e->pos()+ delta.toPointF());
    b->setSpeed(speed);
    b->setPixmap(QPixmap(picUrl));
    e->scene()->addItem(b);
    return b;
}
