#ifndef CONFIG_H
#define CONFIG_H

#include "qglobal.h"


//GAME CONFIG
const int WIDTH = 800;
const int HEIGHT = 1000;
const qreal FPS = 60;
const qreal BULLET_SPEED = 10;
const qreal PLAYER_MOVING_SPEED = 10;

const qreal PLAYER_HP = 10;
const qreal PLAYER_ATK = 1;
const qreal ENEMY_HP = 10;
const qreal ENEMY_ATK = 1;
const qreal DEFAULT_ATK = 1; //子弹的默认攻击力
const qreal PLAYER_SHOOT_PERIOD = 5;
const qreal HIDEN_EDGE = 500; //不显示的宽度

//MAGIC NUMBER
const int BOSS_DATA_TAG = 1;



#endif // CONFIG_H
