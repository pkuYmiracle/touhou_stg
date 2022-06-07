#include "scenario.h"
#include "game/config.h"
#include "qdebug.h"

Scenario::Scenario()
{

}

Scenario &Scenario::add(qreal time, QPointF loc, EnemyPrototype &ep) {
    enemies.push_back({{time, loc}, ep});
    return *this;
}

void Scenario::start(QGraphicsScene *scene) {
    for(auto p : enemies) {
        QTimer::singleShot(p.first.first * 1000, scene, [=]{
            p.second.spawnIt(scene, p.first.second);
        });
    }
}

//bool Scenario::isCompleted() const {
//    return boss->scene() != 0;
//}


std::vector<Scenario> scenarios;
void makeScenarios(){
    Scenario s;
    s
            .add(0, {-100, -100}, *enemyPrototypes[0]) //在屏幕之外生成不会这么突兀
            .add(5, {-200, 200}, *enemyPrototypes[0]); //屏幕显示范围左上角(0,0)右下角(WIDTH,HEIGHT) 左右是x，上下是y

    scenarios.push_back(s);
}
