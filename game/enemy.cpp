#include "enemy.h"
#include "config.h"

Enemy::Enemy()
{
    this->setPixmap(QPixmap(":/game/assets/player.png")); //@TODO
    this->setHp(ENEMY_HP);
}
