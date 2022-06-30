#include "bullet.h"

void Bullet::setLauncher(LivingEntity *newLauncher) { launcher = newLauncher; }

LivingEntity *Bullet::getLauncher() const { return launcher; }

qreal Bullet::getAtk() const { return atk; }

void Bullet::setAtk(qreal newAtk) { atk = newAtk; }

Bullet::Bullet(LivingEntity *e) : launcher(e) {
    // default asset.
    this->setPixmap(QPixmap(":/game/assets/bullet.png"));
    this->setShapeMode(
        QGraphicsPixmapItem::BoundingRectShape);  // for performance
}
