#include "enemyprototype.h"
#include "game/action.hpp"
#include "qdebug.h"
#include "qgraphicsscene.h"
#include "qnamespace.h"
#include <QTimer>


EnemyPrototype::EnemyPrototype(QString picUrl)
    : actions(), picUrl(picUrl)
{

}

EnemyPrototype& EnemyPrototype::operator>>(Action *action)
{
    actions.push_back(action);
    return *this;
}

Enemy *EnemyPrototype::spawnIt(QGraphicsScene *scene, QPointF initLoc)
{
    qreal nowTime = 0;
    Enemy *e = new Enemy();
    e->setPixmap(QPixmap(picUrl));
    e->setPos(initLoc);

    //a terrible impl.... but it works.
    for (auto act : actions) {
        if (act->isMove()) {
            Move *move = dynamic_cast<Move*>(act);
            //it would be call only when e has not been destroyed.
            QTimer::singleShot(nowTime * 1000,
                        Qt::TimerType::PreciseTimer,
                        e,
                        [=]{
                            if(e->scene()) //还没有被scene移除
                                e->setSpeed(move->getSpeed());
                        });
        } else {
            Attack *atk = dynamic_cast<Attack*>(act);
            QTimer::singleShot(nowTime * 1000,
                        Qt::TimerType::PreciseTimer,
                        e,
                        [=]{
                            if(e->scene()) //还没有被scene移除
                                atk->getBulletGroup().spawnBullteGroupFrom(e);
                        });
        }
        nowTime += act->getDuration();
    }
    scene->addItem(e);
    return e;
}

EnemyPrototype::~EnemyPrototype() {
    for (auto a : actions) {
        delete a;
    }
}


std::vector<EnemyPrototype*> enemyPrototypes;
void makeEnemyPrototypes() {
    //以下是一个预置EP实例
    EnemyPrototype *ep = new EnemyPrototype();
    (*ep)   >> (new Attack(bulletGroups[0], 1))
            >> (new Attack(bulletGroups[0], 1))
            >> (new Attack(bulletGroups[0], 1))
            >> (new Attack(bulletGroups[0], 1))
            >> (new Move({1, 1}, 3))
            >> (new Move({0, 0}, 3));
    enemyPrototypes.push_back(ep);
}

