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
    BulletGroup bg_blue01;
    bg_blue01.bullets.push_back(BulletPrototype({8.7, 7.5}, {1.732, 1.5},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({7.5, 8.7}, {1.5, 1.732},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({-7.5, 8.7}, {-1.5, 1.732},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({-8.7, 7.5}, {-1.732, 1.5},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({-8.7, -7.5}, {-1.732, -1.5},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({-7.5, -8.7}, {-1.5, -1.732},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({7.5, -8.7}, {1.5, -1.732},1,":/game/assets/bullet_blue02.png"));
    bg_blue01.bullets.push_back(BulletPrototype({8.7, -7.5}, {1.732, -1.5},1,":/game/assets/bullet_blue02.png"));
    bulletGroups.push_back(bg_blue01);
    BulletGroup bg_blue02;
    bg_blue02.bullets.push_back(BulletPrototype({0.00,5.00},{0.00,2.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({2.50,4.33},{1.00,1.73},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({4.33,2.50},{1.73,1.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({5.00,0.00},{2.00,0.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({4.33,-2.50},{1.73,-1.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({2.50,-4.33},{1.00,-1.73},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({0.00,-5.00},{0.00,-2.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({-2.50,-4.33},{-1.00,-1.73},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({-4.33,-2.50},{-1.73,-1.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({-5.00,-0.00},{-2.00,-0.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({-4.33,2.50},{-1.73,1.00},1,":/game/assets/bullet_blue04.png"));
    bg_blue02.bullets.push_back(BulletPrototype({-2.50,4.33},{-1.00,1.73},1,":/game/assets/bullet_blue04.png"));
    bulletGroups.push_back(bg_blue02);
    BulletGroup bg_blue03;
    bg_blue03.bullets.push_back(BulletPrototype({4.33,2.50},{1.73,1.00},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({3.54,3.54},{1.41,1.41},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({2.50,4.33},{1.00,1.73},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({1.29,4.83},{0.52,1.93},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({0.00,5.00},{0.00,2.00},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({-1.29,4.83},{-0.52,1.93},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({-2.50,4.33},{-1.00,1.73},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({-3.54,3.54},{-1.41,1.41},1,":/game/assets/bullet_blue03.png"));
    bg_blue03.bullets.push_back(BulletPrototype({-4.33,2.50},{-1.73,1.00},1,":/game/assets/bullet_blue03.png"));
    bulletGroups.push_back(bg_blue03);
    BulletGroup bg_yellow_star;
    bg_yellow_star.bullets.push_back(BulletPrototype({0.00,-5.00},{0.00,-4.00},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({4.76,-1.55},{3.80,-1.24},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({2.94,4.05},{2.35,3.24},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({-2.94,4.05},{-2.35,3.24},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({-4.76,-1.55},{-3.80,-1.24},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({0.00,5.00},{0.00,2.00},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({-4.76,1.55},{-1.90,0.62},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({-2.94,-4.05},{-1.18,-1.62},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({2.94,-4.05},{1.18,-1.62},1,":/game/assets/bullet_yellow.png"));
    bg_yellow_star.bullets.push_back(BulletPrototype({4.76,1.55},{1.90,0.62},1,":/game/assets/bullet_yellow.png"));
    bulletGroups.push_back(bg_yellow_star);
}
