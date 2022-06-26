#include "bulletgroup.h"

BulletGroup::BulletGroup()
    : bullets()
{

}

void BulletGroup::spawnBulletGroupFrom(LivingEntity *e) const
{
    for(const auto &pt : bullets) {
        pt.spawnBulletFrom(e);
    }
}


//     预置bullet groups，将会在GC开始时调用
std::vector<BulletGroup> bulletGroups;
void initBulletGroups() {
    //这是一个预置bulletGroups的实例
    BulletGroup bg;
    // 一个bulletGroups可以被某个LivingEntity发射，包含若干颗bullet.
    // 每个bullet由一个bulletPrototype生成. 具体参数见构造函数
    bg.bullets.push_back(BulletPrototype({10, 10}, {1, 1}));
    bg.bullets.push_back(BulletPrototype({-10, 10}, {-1, 1}));
    bg.bullets.push_back(BulletPrototype({10, -10}, {1, -1}));
    bg.bullets.push_back(BulletPrototype({-10, -10}, {-1, -1}));
    bulletGroups.push_back(bg);
}
