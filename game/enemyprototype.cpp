#include "enemyprototype.h"

#include <QObject>
#include <QTimer>

#include "game/action.hpp"
#include "game/config.h"
#include "game/gamecontroller.h"
#include "qdebug.h"
#include "qgraphicsscene.h"
#include "qnamespace.h"

int EnemyPrototype::getHp() const { return hp; }

void EnemyPrototype::setHp(int newHp) { hp = newHp; }

EnemyPrototype::EnemyPrototype(QString picUrl, int hp, bool _is_boss)
    : actions(), picUrl(picUrl), hp(hp), is_boss(_is_boss) {}

EnemyPrototype::EnemyPrototype(const EnemyPrototype &e) {
    actions.clear();
    is_boss = e.is_boss;
    for (auto a : e.actions) {
        this->actions.push_back(a->clone());
    }
    picUrl = e.picUrl;
    hp = e.hp;
}

EnemyPrototype::EnemyPrototype(EnemyPrototype &&e) {
    picUrl = e.picUrl;
    hp = e.hp;
    actions = std::move(e.actions);
    is_boss = e.is_boss;
}

EnemyPrototype &EnemyPrototype::operator=(const EnemyPrototype &e) {
    if (&e == this) return *this;
    for (auto a : actions) {
        delete a;
    }
    actions.clear();
    for (auto a : e.actions) {
        this->actions.push_back(a->clone());
    }
    hp = e.hp;
    picUrl = e.picUrl;
    is_boss = e.is_boss;
    return *this;
}

EnemyPrototype &EnemyPrototype::operator<<(Action *action) {
    actions.push_back(action);
    return *this;
}

Enemy *EnemyPrototype::spawnIt(GameController *gc, QPointF initLoc) const {
    auto scene = gc->getScene();
    qreal nowTime = 0;
    Enemy *e = new Enemy();
    e->setPixmap(QPixmap(picUrl));
    e->setPos(initLoc);
    e->setHp(this->hp);

    // a terrible impl.... but it works.
    for (auto act : actions) {
        if (act->isMove()) {
            Move *move = dynamic_cast<Move *>(act);
            // it would be call only when e has not been destroyed.
            gc->createOneShotTimer(
                nowTime * 1000, e,
                [_ = move->clone(), e] {  //此处不clone会造成悬垂指针
                    if (e->scene())       //还没有被scene移除
                        e->setSpeed(_->getSpeed());
                });
        } else {
            Attack *atk = dynamic_cast<Attack *>(act);
            gc->createOneShotTimer(
                nowTime * 1000, e,
                [_ = atk->clone(), e] {  //此处不clone会造成悬垂指针
                    if (e->scene())      //还没有被scene移除
                        _->getBulletGroup().spawnBulletGroupFrom(e);
                });
        }
        nowTime += act->getDuration();
    }
    if (this->is_boss) {
        e->setScale(1.8);
    }
    scene->addItem(e);
    return e;
}

EnemyPrototype::~EnemyPrototype() {
    for (auto a : actions) {
        delete a;
    }
}

std::vector<EnemyPrototype *> enemyPrototypes_boss, enemyPrototypes_small;
void init_boss() {
    QString e_picUrl = ":/game/assets/enemy.png";  //每一组怪的图
    int e_hp = ENEMY_HP*2;                           //每一组怪的血
    EnemyPrototype *ep =
        new EnemyPrototype(e_picUrl, e_hp, 1);  //最后一个参数为1：表示boss
    // 为一个EnemyPrototype设置动作序列，参数的意义具体见各个动作的构造函数
    (*ep) << (new Attack(bulletGroups[0], 2))
          << (new Attack(bulletGroups[1], 2))
          << (new Attack(bulletGroups[2], 2))
          << (new Attack(bulletGroups[3], 2))
          << (new Attack(bulletGroups[4], 2))
          << (new Attack(bulletGroups[5], 2))
          << (new Attack(bulletGroups[6], 2))
          << (new Attack(bulletGroups[7], 2));
    enemyPrototypes_boss.push_back(ep);
    for (int i = 0; i < 10; i++) {
        QString e_picUrl = ":/game/assets/enemy.png";  //每一组怪的图
        int e_hp = ENEMY_HP * (rand() % 3 + 2);        //每一组怪的血

        EnemyPrototype *ep =
            new EnemyPrototype(e_picUrl, e_hp, 1);  //最后一个参数为1：表示boss
        // 为一个EnemyPrototype设置动作序列，参数的意义具体见各个动作的构造函数
        for (int t = 0; t < 30; t++) {
            if (rand() % 4) {
                int id = rand() % bulletGroups.size();

                qreal t = (qreal)(rand() % 20 + 1);
                t /= 10;
                (*ep) << (new Attack(bulletGroups[id], t));
            } else {
                qreal t = (qreal)(rand() % 20 + 1);
                t /= 10;
                qreal x = (qreal)(rand() % 15 + 1);
                x /= 10;
                qreal y = (qreal)(rand() % 15 + 1);
                y /= 10;
                *ep << (new Move({x, y}, t));
                *ep << (new Move({0, 0}, t + 1));
            }
            if(t % 3 == 0)
            {
                int id = rand() % boss_bulletGroups.size();

                qreal t = (qreal)(rand() % 10 + 1);
                t /= 10;
                (*ep) << (new Attack(boss_bulletGroups[id], t));
            }
        }
        enemyPrototypes_boss.push_back(ep);
    }
}
void init_small() {
    QString e_picUrl = ":/game/assets/enemy07.png";
    int e_hp = ENEMY_HP * 3;  //每一组怪的血
    EnemyPrototype *ep1 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small enemy
    (*ep1) << (new Move({3, 3}, 1.3)) << (new Attack(bulletGroups[4], 1.5))
           << (new Move({0, 0}, 1.3)) << (new Attack(bulletGroups[4], 0))
           << (new Move({3, 3}, 0.4));
    enemyPrototypes_small.push_back(ep1);
    enemyPrototypes_small.push_back(ep1);

    e_hp *= 0.5;
    e_picUrl = ":/game/assets/small_enemy04.png";
    EnemyPrototype *eps2 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small
                                                                   // enemy
    (*eps2) << (new Move({4, 0}, 1.5)) << (new Move({0, 0}, 0))
            << (new Attack(bulletGroups[5], 0.3))
            << (new Attack(bulletGroups[5], 0.3))
            << (new Attack(bulletGroups[5], 0.3))
            << (new Attack(bulletGroups[5], 0.3)) << (new Move({4, 0}, 1));

    enemyPrototypes_small.push_back(eps2);
    e_picUrl = ":/game/assets/enemy05.png";
    EnemyPrototype *ep3 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small enemy
    (*ep3) << (new Move({-3, 3}, 0.7)) << (new Attack(bulletGroups[6], 1.5))
           << (new Move({0, 0}, 1)) << (new Attack(bulletGroups[6], 0))
           << (new Move({-3, -3}, 0.7));
    enemyPrototypes_small.push_back(ep3);

    e_hp *= 2;
    e_picUrl = ":/game/assets/small_enemy02.png";
    EnemyPrototype *ep4 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small enemy
    (*ep4) << (new Move({0, 1.5}, 0.7)) << (new Attack(bulletGroups[3], 1.5))
           << (new Move({0, 0}, 1)) << (new Attack(bulletGroups[3], 0))
           << (new Move({-2, 1}, 0.7));
    enemyPrototypes_small.push_back(ep4);
    EnemyPrototype *ep5 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small enemy
    (*ep5) << (new Move({0, 1.5}, 0.7)) << (new Attack(bulletGroups[3], 1.5))
           << (new Move({0, 0}, 1)) << (new Attack(bulletGroups[3], 0))
           << (new Move({2, 1}, 0.7));
    enemyPrototypes_small.push_back(ep5);

    e_hp *= 2;
    e_picUrl = ":/game/assets/enemy07.png";
    EnemyPrototype *ep6 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small enemy
    (*ep6) << (new Move({3, 3}, 1.6)) << (new Move({0, 0}, 1))
           << (new Attack(bulletGroups[7], 1))
           << (new Attack(bulletGroups[7], 1))
           << (new Attack(bulletGroups[7], 0)) << (new Move({1.5, -1.5}, 0.7));
    enemyPrototypes_small.push_back(ep6);

    e_picUrl = ":/game/assets/enemy07.png";
    EnemyPrototype *ep7 = new EnemyPrototype(e_picUrl, e_hp, 0);  // small enemy
    (*ep7) << (new Move({3, 3}, 1.6)) << (new Move({0, 0}, 1))
           << (new Attack(bulletGroups[7], 0))
           << (new Attack(bulletGroups[8], 0.5))
           //<<(new Attack(bulletGroups[7], 0))
           << (new Move({1.5, -1.5}, 0.7));
    enemyPrototypes_small.push_back(ep7);
    std::vector<QString> pic_urls;
    pic_urls.push_back(":/game/assets/enemy07.png");
    pic_urls.push_back(":/game/assets/enemy06.png");
    pic_urls.push_back(":/game/assets/enemy05.png");
    pic_urls.push_back(":/game/assets/enemy04.png");
    pic_urls.push_back(":/game/assets/enemy03.png");
    pic_urls.push_back(":/game/assets/enemy02.png");
    pic_urls.push_back(":/game/assets/enemy01.png");
    for (int i = 0; i < 40; i++) {
        QString e_picUrl = pic_urls[rand() % pic_urls.size()];  //每一组怪的图
        qreal e_hp = ENEMY_HP;  //每一组怪的血
        e_hp *= (2 + rand() % 10);
        EnemyPrototype *ep =
            new EnemyPrototype(e_picUrl, e_hp, 0);  //最后一个参数为0：表示小怪
        // 为一个EnemyPrototype设置动作序列，参数的意义具体见各个动作的构造函数
        int T = rand() % (std::min(i + 2,10)) + 5;
        for (int t = 0; t < T; t++) {
            if (rand() % 2) {
                int id = rand() % bulletGroups.size();

                qreal t = (qreal)(rand() % 20 + 1);
                t /= 10;
                (*ep) << (new Attack(bulletGroups[id], t));
            } else {
                qreal t = (qreal)(rand() % 20 + 1);
                t /= 10;
                qreal x = (qreal)(rand() % 10 + 1);
                x /= 10;
                qreal y = (qreal)(rand() % 10 + 1);
                y /= 10;
                *ep << (new Move({x, y}, t));
            }
        }
        enemyPrototypes_small.push_back(ep);
    }
}
void initEnemyPrototypes() {
    init_boss();   //生成boss
    init_small();  //生成小怪
    //以下是一个预置EP实例
}
