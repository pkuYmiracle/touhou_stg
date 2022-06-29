#include "game/bullet.h"
#include "game/config.h"
#include "game/gamecontroller.h"
#include "game/keyboardhandler.hpp"
#include "game/livingentity.h"
#include "qgraphicsscene.h"
#include "qnamespace.h"
#include <QDebug>
#include <QSound>
#include <assert.h>

BulletGroup *Player::getBulletGroup() const
{
    return bulletGroup;
}

void Player::setBulletGroup(BulletGroup *newBulletGroup)
{
    bulletGroup = newBulletGroup;
}

Player::Player(GameController *gc, QString pixmap_url)
    : gc(gc)
{
    QPixmap pixmap = QPixmap(pixmap_url);
    pixmap = pixmap.scaled(30,50);
    this->setPixmap(pixmap);
    this->setHp(PLAYER_HP);
    bulletGroup = 0;
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

    qreal speed_rates = kb->isKeyPressed(Qt::Key_Shift) ? PLAYER_MOVING_SPEED / 3 : PLAYER_MOVING_SPEED;

    if (speed.length() != 0) {
        speed *= speed_rates / speed.length();
    }

    //shoot
    if (kb->isKeyPressed(Qt::Key_Z)) {
        static int cnt = 0;
        if ((++cnt) == PLAYER_SHOOT_PERIOD) {
            cnt = 0;

            assert(this->bulletGroup != 0);
            this->bulletGroup->spawnBulletGroupFrom(this);
//            Bullet *bullet = new Bullet(this);
//            bullet->setAtk(PLAYER_ATK);
//            bullet->setPos(x(), y() - bullet->boundingRect().height());
//            bullet->setSpeed(QVector2D(0, -BULLET_SPEED));
//            this->scene()->addItem(bullet);
        }
    }
}
