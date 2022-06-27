#include "gamecontroller.h"
#include "baseboard.h"
#include "game/bulletgroup.h"
#include "game/enemyprototype.h"
#include "game/pauseboard.h"
#include "game/scenario.h"
#include "keyboardhandler.hpp"
#include "mypushbottom.h"
#include "qnamespace.h"
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
    frame_timer(new QTimer(this)),
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
//    view->setWindowFlag(Qt::FramelessWindowHint);
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
    QObject::connect(frame_timer, &QTimer::timeout, scene, [=]{
        scene->advance();
        update_game_info();
    });
    view->installEventFilter(kbhandler);

    view->setBackgroundBrush(QBrush(QPixmap(":/game/assets/background.jpg")));

    //        view->setFixedSize(WIDTH, HEIGHT);
    view->setFixedSize(view->sizeHint());
    view->show();
    frame_timer->start(1000 / FPS);

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
    return !frame_timer->isActive();
}

void GameController::gameContinue() {
    for (auto widget : pauseboard_widgets) {
        widget->hide();
    }

    frame_timer->start();
    for (auto &pair : timers) if (pair.timer->remainingTime() > 0) {
        pair.timer->setInterval(pair.remainingTime);
        pair.timer->start();
        pair.remainingTime = 0;
    }
    scene->removeItem(this->pause_shield);
}

void GameController::showPauseboard() {
    Mypushbottom *continue_button = new Mypushbottom(view, true,
                                                  ":/game/assets/button.png",150);
    Mypushbottom *mainmenu_button = new Mypushbottom(view, true,
                                                  ":/game/assets/button.png",150); //TODO
    continue_button->resize(500,100);
    QPoint delta = {
        continue_button->rect().width() / 2,
        continue_button->rect().height() / 2
    };
    continue_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y());
    continue_button->show();


    mainmenu_button->resize(500,100);
    mainmenu_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y() - 120);
    mainmenu_button->show();

    connect(continue_button, &Mypushbottom::clicked, continue_button, [&](){
        QTimer::singleShot(300, this,[&](){
            this->gameContinue();
        });
    });


    connect(mainmenu_button, &Mypushbottom::clicked, mainmenu_button ,[&](){
        QTimer::singleShot(300, this, [&](){
            //@TODO
        });
    });


    pauseboard_widgets = std::vector<QWidget*>({continue_button, mainmenu_button});
}

void GameController::pause() {
    frame_timer->stop();
    for (auto &pair : timers) if (pair.timer->remainingTime() > 0) {
        pair.remainingTime = pair.timer->remainingTime();
        pair.timer->stop();
    }
    this->pause_shield = scene->addRect(scene->sceneRect(), QPen(), QBrush(QColor(255,255,255,100)));
    this->showPauseboard();
}

KeyboardHandler *GameController::getKbhandler() const
{
    return kbhandler;
}
