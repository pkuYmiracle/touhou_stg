#include "game/bullet.h"
#include "game/gamecontroller.hpp"
#include "game/keyboardhandler.hpp"
#include "game/livingentity.h"
#include "qnamespace.h"
#include <QDebug>

Player::Player(GameController *gc) : gc(gc)
{
    this->setPixmap(QPixmap(":/people/orange.png"));
}

void Player::advance(int phase)
{
    if (phase == 1) return;
    LivingEntity::advance(phase);

    // updating speed vector
    KeyboardHandler *kb = this->gc->getKbhandler();
    speed = {0, 0};
    if (kb->isKeyPressed(Qt::Key_Up)) {
        speed += {0, -1};
    }
    if (kb->isKeyPressed(Qt::Key_Down)) {
        speed += {0, 1};
    }
    if (kb->isKeyPressed(Qt::Key_Left)) {
        speed += {-1, 0};
    }
    if (kb->isKeyPressed(Qt::Key_Right)) {
        speed += {+1, 0};
    }
    if (speed.dotProduct(speed, speed) > 0.001) {
        speed /= sqrt(speed.dotProduct(speed, speed));
        speed *= PLAYER_MOVING_SPEED;
    }
    //shoot
    if (kb->isKeyPressed(Qt::Key_Z)) {
        Bullet *bullet = new Bullet();
        bullet->setPos(x(), y() - 10);
        bullet->setSpeed(QPointF(0, -BULLET_SPEED));
        this->scene()->addItem(bullet);
    }
}
