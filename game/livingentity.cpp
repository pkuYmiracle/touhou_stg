#include "bullet.h"
#include "livingentity.h"
#include "qdebug.h"
#include <QGraphicsScene>
#include <assert.h>
#include <QSound>
#include <QMediaPlayer>

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
            continue;
        } else
        if (e->isBullet()) {
            Bullet *bullet = dynamic_cast<Bullet*>(e);
            if (!bullet) assert(0);
            if ((this->isPlayer() && bullet->getLauncher()->isEnemy())
                || (this->isEnemy() && bullet->getLauncher()->isPlayer())) { //Player to Enemy, or, Enemy to Player
                this->hp -= bullet->getAtk();
                this->scene()->removeItem(bullet);
//                bullet->deleteLater();


                //player hitted sound effect
                if (this->isPlayer()) {
                    qDebug() << "wav" << endl;
                    static bool inited = 0;
                    static QMediaPlayer *player = new QMediaPlayer;
                    if (!inited) {
                        inited = 1;
                        player->setMedia(QUrl("qrc:/game/assets/sound/se_damage00.wav"));
                        player->setVolume(25);
                    }
                    player->play();
                }
            }
        }
    }

    // die:
    if (this->hp <= 0) {
        this->scene()->removeItem(this);
//        this->deleteLater();
    }
}
