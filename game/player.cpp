#include "game/bullet.h"
#include "game/gamecontroller.h"
#include "game/keyboardhandler.hpp"
#include "game/livingentity.h"
#include "qnamespace.h"
#include <QDebug>

Player::Player(GameController *gc) : gc(gc)
{
    this->setPixmap(QPixmap(":/game/assets/player.png"));
    this->setHp(PLAYER_HP);
}

void Player::advance(int phase)
{
    if (phase == 1) return;
    if (scene() == 0) return;
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
    if (speed.length() != 0) {
        speed *= PLAYER_MOVING_SPEED / speed.length();
    }

    //shoot
    if (kb->isKeyPressed(Qt::Key_Z)) {
        static int cnt = 0;
        if ((++cnt) == PLAYER_SHOOT_PERIOD) {
            cnt = 0;
            Bullet *bullet = new Bullet(this);
            bullet->setAtk(PLAYER_ATK);

//            bullet->setPos(x(), y() - 10);
            bullet->setPos(x(), y() - bullet->boundingRect().height());
//            qDebug() << bullet->pos() << endl;
            bullet->setSpeed(QVector2D(0, -BULLET_SPEED));
            this->scene()->addItem(bullet);
        }
    }
}
