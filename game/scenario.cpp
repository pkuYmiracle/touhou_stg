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
    double t_=0;
    //一个关卡由很多enemy组成. 一个enemy由一个enemyPrototypes生成
    s   .add(t_, {500, 500}, *enemyPrototypes[0]);t_=+15;//展示一下所有bulletgroup
    s
        .add(t_, {25, 25}, *enemyPrototypes[1]); //在屏幕之外生成不会这么突兀
        t_+=3;
    s    .add(t_, {800, 25}, *enemyPrototypes[3]);//屏幕显示范围左上角(0,0)右下角(WIDTH,HEIGHT) 左右是x，上下是y
        t_+=3;
    s
                //下面这六只一起飞
        .add(t_, {500, 0}, *enemyPrototypes[4])
        .add(t_, {500, 0}, *enemyPrototypes[5])
        .add(t_+0.5, {500, 0}, *enemyPrototypes[4])
        .add(t_+0.5, {500, 0}, *enemyPrototypes[5])
        .add(t_+1, {500, 0}, *enemyPrototypes[4])
        .add(t_+1, {500, 0}, *enemyPrototypes[5]);
        //
        t_+=5;
    s
            .add(t_, {0, 300}, *enemyPrototypes[2])
            .add(t_+0.7, {0, 450}, *enemyPrototypes[2])
            .add(t_+1.4, {0, 600}, *enemyPrototypes[2]);
        t_+=5;
        s   .add(t_, {0, 100}, *enemyPrototypes[6]);
        t_+=5;
        s   .add(t_, {0, 100}, *enemyPrototypes[7]);
    /*s   .add(t_, {0, 100}, *enemyPrototypes[6])
        .add(0, {500, 500}, *enemyPrototypes[0]) //在屏幕之外生成不会这么突兀
        .add(0, {530, 500}, *enemyPrototypes[0])
        .add(0, {550, 500}, *enemyPrototypes[0])
        .add(0, {500, 400}, *enemyPrototypes[0])
        .add(0, {540, 300}, *enemyPrototypes[0])
        .add(0, {550, 200}, *enemyPrototypes[0])
        .add(5, {10, 10}, *enemyPrototypes[0]) //屏幕显示范围左上角(0,0)右下角(WIDTH,HEIGHT) 左右是x，上下是y
        .add(0, {500, 500}, *enemyPrototypes[0]) //在屏幕之外生成不会这么突兀
        .add(0, {530, 500}, *enemyPrototypes[0])
        .add(0, {550, 500}, *enemyPrototypes[0])
        .add(0, {500, 400}, *enemyPrototypes[0])
        .add(0, {250, 100}, *enemyPrototypes[0])
        .add(0, {300, 200}, *enemyPrototypes[0])
        .add(0, {600, 300}, *enemyPrototypes[0])
        .add(0, {540, 300}, *enemyPrototypes[0])
        .add(0, {550, 200}, *enemyPrototypes[0])
        .add(5, {10, 10}, *enemyPrototypes[0]);*/ //屏幕显示范围左上角(0,0)右下角(WIDTH,HEIGHT) 左右是x，上下是y
    scenarios.push_back(s);
}
