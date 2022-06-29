#include "bulletgroup.h"
#include<bits/stdc++.h>

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

#define M_PI 3.14159265358979323846
double pi=3.14;
//     预置bullet groups，将会在GC开始时调用
void generate_bg(BulletGroup &bg,double bg_atk,QString bg_picUrl,double n0,double n1,double n2,double n3=0){//生成圆（n0等分；半径n1;速度n2;相位n3)
    for(int i=0;i<n0;i++)bg.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0+n3)),static_cast<float>(n1*sin(2*pi*i/n0+n3))},{static_cast<float>(n2*cos(2*pi*i/n0+n3)),static_cast<float>(n2*sin(2*pi*i/n0+n3))},bg_atk,bg_picUrl));
}
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
    generate_bg(bg_blue02,1,":/game/assets/bullet_blue04.png",12,5,2,0);
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
    BulletGroup bg_yellow_star;//4
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
    double bg_atk = 2,n0=18,n1=5,n2=5;//n1是起始半径，n2控制速度，n0即将圆n0等分
    QString bg_picUrl = ":/game/assets/bullet_red02.png";
    BulletGroup bg_05,bg_06,bg_07,bg_08,bg_09,bg_10,bg_11,bg_12,bg_13;
    bg_05.bullets.push_back(BulletPrototype({5,0},{-3,1.5},bg_atk,bg_picUrl));
    bg_05.bullets.push_back(BulletPrototype({5,0},{3,1.5},bg_atk,bg_picUrl));

    bulletGroups.push_back(bg_05);//左下+右下
    bg_picUrl=":/game/assets/bullet_red02.png";
    for(int i=0;i<n0;i++)bg_06.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0)),static_cast<float>(n1*sin(2*pi*i/n0))},{static_cast<float>(n2*cos(2*pi*i/n0)),static_cast<float>(n2*sin(2*pi*i/n0))},bg_atk,bg_picUrl));
    n1=0;n2=3;
    for(int i=0;i<n0;i++)bg_06.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0+pi*0.3)),static_cast<float>(n1*sin(2*pi*i/n0+pi*0.3))},{static_cast<float>(n2*cos(2*pi*i/n0+pi*0.3)),static_cast<float>(n2*sin(2*pi*i/n0+pi*0.3))},bg_atk,bg_picUrl));
    bulletGroups.push_back(bg_06);//两层红色圈
    bg_picUrl=":/game/assets/bullet_red03.png";
    n0=3;n2=4;
    for(int i=0;i<n0;i++)bg_07.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0)),static_cast<float>(n1*sin(2*pi*i/n0))},{static_cast<float>(n2*cos(2*pi*i/n0)),static_cast<float>(n2*sin(2*pi*i/n0))},bg_atk,bg_picUrl));
    n1=0;n2=2;
    for(int i=0;i<n0;i++)bg_07.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0+pi/3)),static_cast<float>(n1*sin(2*pi*i/n0+pi/3))},{static_cast<float>(n2*cos(2*pi*i/n0+pi/3)),static_cast<float>(n2*sin(2*pi*i/n0+pi/3))},bg_atk,bg_picUrl));
    bulletGroups.push_back(bg_07);//三角
    bg_picUrl=":/game/assets/bullet_red03.png";
    n0=3;n2=2;
    for(int i=0;i<n0;i++)bg_08.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0)),static_cast<float>(n1*sin(2*pi*i/n0))},{static_cast<float>(n2*cos(2*pi*i/n0)),static_cast<float>(n2*sin(2*pi*i/n0))},bg_atk,bg_picUrl));
    n1=0;n2=4;
    for(int i=0;i<n0;i++)bg_08.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0+pi/3)),static_cast<float>(n1*sin(2*pi*i/n0+pi/3))},{static_cast<float>(n2*cos(2*pi*i/n0+pi/3)),static_cast<float>(n2*sin(2*pi*i/n0+pi/3))},bg_atk,bg_picUrl));

    bulletGroups.push_back(bg_08);

    //玩家的bg_09 to bg_12
    bg_picUrl=":/game/assets/bullet_red05";
    bg_09.bullets.push_back(BulletPrototype({0,-8},{0,-4},bg_atk,bg_picUrl));
    bg_picUrl=":/game/assets/bullet_red03";
    bg_atk=1;
    bg_09.bullets.push_back(BulletPrototype({-4,-4},{-3,-4},bg_atk,bg_picUrl));
    bg_09.bullets.push_back(BulletPrototype({4,-4},{3,-4},bg_atk,bg_picUrl));
    bulletGroups.push_back(bg_09);//三个方向的
    bg_picUrl=":/game/assets/bullet_blue05";
    bg_atk=1.5;
    bg_10.bullets.push_back(BulletPrototype({0,-8},{0,-4},bg_atk,bg_picUrl));
    bulletGroups.push_back(bg_10);//一个方向但是攻击力强的蓝色圆
    bg_picUrl=":/game/assets/bullet_pink01";
    bg_atk=0.6;
    bg_11.bullets.push_back(BulletPrototype({0.00,-5.00},{0.00,-4.00},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({4.76,-1.55},{3.80,-1.24},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({2.94,4.05},{2.35,3.24},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({-2.94,4.05},{-2.35,3.24},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({-4.76,-1.55},{-3.80,-1.24},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({0.00,5.00},{0.00,2.00},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({-4.76,1.55},{-1.90,0.62},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({-2.94,-4.05},{-1.18,-1.62},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({2.94,-4.05},{1.18,-1.62},bg_atk,bg_picUrl));
    bg_11.bullets.push_back(BulletPrototype({4.76,1.55},{1.90,0.62},bg_atk,bg_picUrl));
    bulletGroups.push_back(bg_11);//鸡肋的粉色星星
    bg_picUrl=":/game/assets/bullet_blue06";
    bg_atk=0.6;
    n0=12;n1=7;n2=5;
    for(int i=6;i<n0;i++)bg_12.bullets.push_back(BulletPrototype({static_cast<float>(n1*cos(2*pi*i/n0)),static_cast<float>(n1*sin(2*pi*i/n0))},{static_cast<float>(n2*cos(2*pi*i/n0)),static_cast<float>(n2*sin(2*pi*i/n0))},bg_atk,bg_picUrl));
    bulletGroups.push_back(bg_12);//鸡肋的蓝色扇
    generate_bg(bg_13,0.35,":/game/assets/bullet_yellow2",10,7,5);
    bulletGroups.push_back(bg_13);
}

