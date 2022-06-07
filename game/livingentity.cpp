#include "bullet.h"
#include "livingentity.h"
#include "qdebug.h"
#include <QGraphicsScene>
#include <assert.h>

float LivingEntity::getHp() const
{
    return hp;
}

void LivingEntity::setHp(qreal newHp)
{
    hp = newHp;
}

LivingEntity::LivingEntity()
{

}

void LivingEntity::advance(int phase)
{
    if (phase == 1) return;
    if (scene() == 0) return;
    Entity::advance(phase);

    //处理子弹打实体的部分
    const auto itemList = this->collidingItems();

    for (auto item : itemList) {
        Entity *e = dynamic_cast<Entity*>(item);
        if (!e) {
            assert(0);
        } else
        if (e->isBullet()) {
            Bullet *bullet = dynamic_cast<Bullet*>(e);
            if (!bullet) assert(0);
            if ((this->isPlayer() && bullet->getLauncher()->isEnemy())
                || (this->isEnemy() && bullet->getLauncher()->isPlayer())) { //Player to Enemy, or, Enemy to Player
                this->hp -= bullet->getAtk();
                this->scene()->removeItem(bullet);
                bullet->deleteLater();
            }
        }
    }

    // die:
    if (this->hp <= 0) {
        this->scene()->removeItem(this);
        this->deleteLater();
    }
}
