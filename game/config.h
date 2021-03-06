#ifndef CONFIG_H
#define CONFIG_H

#include <QRectF>

#include "qglobal.h"

// GAME CONFIG
const int WIDTH = 1200;
const int HEIGHT = 1000;

const QRectF GAME_BOARD_RECT =
    QRectF(0, 0, 800, 1000);  //游戏界面的大小，剩下的界面展示血量等信息

const QRectF PLAYER_BOARD_RECT =
    QRectF(0, 400, 850, 600);
const qreal FPS = 60;
const qreal BULLET_SPEED = 10;
const qreal PLAYER_MOVING_SPEED = 6;

const qreal PLAYER_HP = 250;
const qreal PLAYER_ATK = 1;
const qreal ENEMY_HP = 20;
const qreal ENEMY_ATK = 1;
const qreal DEFAULT_ATK = 1;  //子弹的默认攻击力
const qreal PLAYER_SHOOT_PERIOD = 10;
const qreal HIDEN_EDGE = 0;  //实际界面大小(-HIDEN_EDGE, -HIDEN_EDGE, WIDTH +
                             //HIDEN_EDGE, HEIGHT + HIDEN_EDGE)
const int BGM_VOLUME = 50;  // out of 100

// MAGIC NUMBER
const int BOSS_DATA_TAG = 1;

#endif  // CONFIG_H
