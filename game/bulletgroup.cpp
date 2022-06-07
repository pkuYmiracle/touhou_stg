#include "bulletgroup.h"

BulletGroup::BulletGroup()
    : bullets()
{

}

void BulletGroup::spawnBullteGroupFrom(LivingEntity *e) const
{
    for(const auto &pt : bullets) {
        pt.spawnBulletFrom(e);
    }
}


//     预置bullet groups，将会在GC开始时调用
std::vector<BulletGroup> bulletGroups;
void makeBulletGroups() {
    //这是一个预置bulletGroups的实例
    BulletGroup bg;

    bg.bullets.push_back(BulletPrototype({100, 100}, {1, 1}));
    bg.bullets.push_back(BulletPrototype({-100, 100}, {-1, 1}));
    bg.bullets.push_back(BulletPrototype({100, -100}, {1, -1}));
    bg.bullets.push_back(BulletPrototype({-100, -100}, {-1, -1}));
    bulletGroups.push_back(bg);
}
