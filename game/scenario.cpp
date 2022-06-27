#include "scenario.h"
#include "game/config.h"
#include "game/gamecontroller.h"
#include "qdebug.h"

Scenario::Scenario()
    : enemySpawnConfig(), enemies()
{

}

// loc: 生成的初始位置
// ep:  使用的EnemyPrototypes
Scenario &Scenario::add(qreal time, QPointF loc, EnemyPrototype &ep) {
    enemySpawnConfig.push_back({{time, loc}, ep});
    return *this;
}

void Scenario::start(GameController *gc) {
    for(const auto &p : enemySpawnConfig) {
        gc->createOneShotTimer(p.first.first * 1000, gc, [p, gc, this]{
            enemies.push_back(p.second.spawnIt(gc, p.first.second));
        });
    }
}

bool Scenario::isCompleted() const {
    for (auto e : enemies) {
        if (e->scene() == 0) return false;
    }
    return true;
}


std::vector<Scenario> scenarios;
void initScenarios(){
    Scenario s;
    //一个关卡由很多enemy组成. 一个enemy由一个enemyPrototypes生成
    s
        .add(0, {500, 500}, *enemyPrototypes[0]) //在屏幕之外生成不会这么突兀
        .add(0, {530, 500}, *enemyPrototypes[0])
        .add(0, {550, 500}, *enemyPrototypes[0])
        .add(0, {500, 400}, *enemyPrototypes[0])
        .add(0, {540, 300}, *enemyPrototypes[0])
        .add(0, {550, 200}, *enemyPrototypes[0])
        .add(5, {10, 10}, *enemyPrototypes[0]); //屏幕显示范围左上角(0,0)右下角(WIDTH,HEIGHT) 左右是x，上下是y

    scenarios.push_back(s);
}
