#include "bullet.h"

void Bullet::setLauncher(LivingEntity *newLauncher)
{
    launcher = newLauncher;
}

LivingEntity *Bullet::getLauncher() const
{
    return launcher;
}

qreal Bullet::getAtk() const
{
    return atk;
}

void Bullet::setAtk(qreal newAtk)
{
    atk = newAtk;
}

Bullet::Bullet(LivingEntity *e)
    : launcher(e)
{
    this->setPixmap(QPixmap(":/game/assets/playerbullet.png"));
}
