#include "gamecontroller.h"
#include "game/bulletgroup.h"
#include "game/enemyprototype.h"
#include "game/scenario.h"
#include "keyboardhandler.hpp"
#include "game/config.h"
#include <qgraphicsview.h>
#include <QString>
#include <QGraphicsTextItem> 
#include <assert.h>
#include <QDebug>
GameController::GameController(const std::vector<QString> &info_ls,QObject *parent ):
    QObject(parent),
    view(new QGraphicsView()),
    scene(new QGraphicsScene(this)),
    frameTimer(new QTimer(this)),
    player(new Player(this)),
    kbhandler(new KeyboardHandler(this)),
    level_name(new QGraphicsTextItem),
    player_hp(new QGraphicsTextItem),
    enemy_hp(new QGraphicsTextItem),
    player_hp_show(new QGraphicsRectItem),
    enemy_hp_show(new QGraphicsRectItem),
    info(info_ls)
{
    initBulletGroups();
    initEnemyPrototypes();
    initScenarios();
    QRect sceneRect = QRect(0, 0, WIDTH, HEIGHT);
    view->setScene(scene);
    player->setPos(GAME_BOARD_RECT.center());
    scene->setSceneRect(sceneRect);
    
    scene->addItem(player);
    qDebug()<< "info_size:" << info.size() << endl;
    level_name ->setPlainText(info[0]);
    level_name ->setPos(QPointF(850,200));
    QFont font;
    font.setPointSize(25);
    level_name ->setFont(font);

     scene->addItem(level_name);

     player_hp ->setPlainText("player hp:");
     player_hp ->setPos(QPointF(850,300));
     player_hp ->setFont(font);

      scene->addItem(player_hp);


      enemy_hp ->setPlainText("enemy hp:");
      enemy_hp ->setPos(QPointF(850,500));
      enemy_hp ->setFont(font);

       scene->addItem(enemy_hp);
        player_hp_show ->setBrush(QBrush(QColor(0,100,100)));
        player_hp_show ->setRect(QRectF(850,400,200,50));
       scene->addItem(player_hp_show);


       scene->addItem(enemy_hp);
        enemy_hp_show ->setBrush(QBrush(QColor(0,100,100)));
        enemy_hp_show ->setRect(QRectF(850,600,200,50));
       scene->addItem(enemy_hp_show);
    scenario = new Scenario(scenarios[0]); // it can only copy before start.
    QObject::connect(frameTimer, &QTimer::timeout, scene, [=]{
        scene->advance();
        update_game_info();
    });
    view->installEventFilter(kbhandler);

    view->setBackgroundBrush(QBrush(QPixmap(":/game/assets/background.jpg")));

    //        view->setFixedSize(WIDTH, HEIGHT);
    view->setFixedSize(view->sizeHint());
    view->show();
    frameTimer->start(1000 / FPS);

    //test code.
    scenario->start(this);
}

GameController::~GameController() {
    view->deleteLater();
    for (auto ep : enemyPrototypes) {
        delete ep;
    }
    //其余成员被Qt自动析构.
}
void GameController::update_game_info(){
    player_hp_show ->setRect(QRectF(850,400,player->getHp()/PLAYER_HP * 200,50));
    enemy_hp_show ->setRect(QRectF(850,600,200,50));
}
QGraphicsScene *GameController::getScene() const
{
    return scene;
}

bool GameController::isPaused() {
    return !frameTimer->isActive();
}

void GameController::gameContinue() {
    frameTimer->start();
}

void GameController::pause() {
    frameTimer->stop();
    for (auto t : timers) {
        qDebug() << t->remainingTime() << endl;
        t->stop();
    }
}

KeyboardHandler *GameController::getKbhandler() const
{
    return kbhandler;
}
