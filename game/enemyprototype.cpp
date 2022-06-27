#include "enemyprototype.h"
#include "game/action.hpp"
#include "game/gamecontroller.h"
#include "qdebug.h"
#include "qgraphicsscene.h"
#include "qnamespace.h"
#include <QTimer>
#include <QObject>

EnemyPrototype::EnemyPrototype(QString picUrl)
    : actions(), picUrl(picUrl)
{

}

EnemyPrototype::EnemyPrototype(const EnemyPrototype &e)
{
    actions.clear();
    for (auto a : e.actions) {
        this->actions.push_back(a->clone());
    }
    picUrl = e.picUrl;
}

EnemyPrototype::EnemyPrototype(EnemyPrototype &&e){
    picUrl = e.picUrl;
    actions = std::move(e.actions);
}

EnemyPrototype &EnemyPrototype::operator=(const EnemyPrototype &e)
{
    if (&e == this) return *this;
    for (auto a : actions) {
        delete a;
    }
    actions.clear();
    for (auto a : e.actions) {
        this->actions.push_back(a->clone());
    }
    picUrl = e.picUrl;
    return *this;
}

EnemyPrototype& EnemyPrototype::operator<<(Action *action)
{
    actions.push_back(action);
    return *this;
}

Enemy *EnemyPrototype::spawnIt(GameController *gc, QPointF initLoc) const
{
    auto scene = gc->getScene();
    qreal nowTime = 0;
    Enemy *e = new Enemy();
    e->setPixmap(QPixmap(picUrl));
    e->setPos(initLoc);

    //a terrible impl.... but it works.
    for (auto act : actions) {
        if (act->isMove()) {
            Move *move = dynamic_cast<Move*>(act);
            //it would be call only when e has not been destroyed.
            gc->createOneShotTimer(nowTime * 1000, e, [_ = move->clone(), e]{//此处不clone会造成悬垂指针
                if(e->scene()) //还没有被scene移除
                    e->setSpeed(_->getSpeed());
            });
        } else {
            Attack *atk = dynamic_cast<Attack*>(act);
            gc->createOneShotTimer(nowTime * 1000, e, [_ = atk->clone(), e]{//此处不clone会造成悬垂指针
                if(e->scene()) //还没有被scene移除
                    _->getBulletGroup().spawnBulletGroupFrom(e);
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
void initEnemyPrototypes() {
    //以下是一个预置EP实例
    EnemyPrototype *ep = new EnemyPrototype();
    // 为一个EnemyPrototype设置动作序列，参数的意义具体见各个动作的构造函数
    (*ep)   << (new Attack(bulletGroups[0], 1))
            << (new Attack(bulletGroups[0], 1))
            << (new Attack(bulletGroups[0], 1))
            << (new Attack(bulletGroups[0], 1))
            << (new Move({10, 10}, 10))
            << (new Move({0, 0}, 0)) //停止
            << (new Move({10, 10}, 100000)); //最后让他飞出屏幕就行
    enemyPrototypes.push_back(ep);
}

