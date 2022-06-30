#include "enemy.h"

#include "config.h"

Enemy::Enemy() {
    // default behaviour
    this->setPixmap(QPixmap(":/game/assets/player.png"));
    this->setHp(ENEMY_HP);
}
