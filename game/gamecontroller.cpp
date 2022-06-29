#include "gamecontroller.h"
#include "baseboard.h"
#include "game/bulletgroup.h"
#include "game/enemyprototype.h"
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
#include "level_menu.h"
#include <QTime>
#include "game/scenario.h"


void GameController:: init_scenario(){
    int id = info[1].toInt();
    qDebug() <<"new_level:"<<id<< ' '<<info[1] << endl;
    scenarios[0].print_boss();
    if (id < scenarios.size())
            this ->scenario = new Scenario (scenarios[0]);
    else
        this ->scenario = new Scenario (Scenario:: gen_random_scenario());
    this->scenario->print_boss();
}

GameController::GameController(const std::vector<QString> &info_ls,Level_menu * from,QObject *parent ):
    QObject(parent),
    father_widget(from),
    view(new QGraphicsView()),
    scene(new QGraphicsScene(this)),
    frame_timer(new QTimer(this)),
    player(new Player(this,info_ls[2])),
    kbhandler(new KeyboardHandler(this)),
    level_name(new QGraphicsTextItem),
    player_hp(new QGraphicsTextItem),
    enemy_hp(new QGraphicsTextItem),
    count_down(new QGraphicsTextItem),
    last_time_count(new QGraphicsTextItem),
    player_hp_show(new QGraphicsRectItem),
    enemy_hp_show(new QGraphicsRectItem),
    info(info_ls),
    bgm_player(new QMediaPlayer)
{
    QRect sceneRect = QRect(0, 0, WIDTH, HEIGHT);
    view->setScene(scene);
//    view->setWindowFlag(Qt::FramelessWindowHint);
    player->setPos(GAME_BOARD_RECT.center().x() + 100,GAME_BOARD_RECT.center().y() + 200);
    scene->setSceneRect(sceneRect);

    scene->addItem(player);
    qDebug()<< "info_size:" << info.size() << endl;
    qDebug()<< info[0]<< endl;
    level_name ->setPlainText(info[0]);
    level_name ->setPos(QPointF(850,200));
    QFont font;
    font.setPointSize(25);
    level_name ->setFont(font);

     scene->addItem(level_name);

     last_time_count ->setPlainText("countdown:");
     last_time_count ->setPos(QPointF(850,300));
     last_time_count ->setFont(font);
     scene->addItem(last_time_count);

     player_hp ->setPlainText("player hp:");
     player_hp ->setPos(QPointF(850,500));
     player_hp ->setFont(font);



      scene->addItem(player_hp);


      enemy_hp ->setPlainText("enemy hp:");
      enemy_hp ->setPos(QPointF(850,700));
      enemy_hp ->setFont(font);

       scene->addItem(enemy_hp);
        player_hp_show ->setBrush(QBrush(QColor(0,100,100)));
        player_hp_show ->setRect(QRectF(850,600,200,50));
       scene->addItem(player_hp_show);


       scene->addItem(enemy_hp);
        enemy_hp_show ->setBrush(QBrush(QColor(0,100,100)));
        enemy_hp_show ->setRect(QRectF(850,800,200,50));
       scene->addItem(enemy_hp_show);
       init_scenario();

       count_down ->setPlainText(QString::number(this->scenario->get_last_time()));
       count_down ->setPos(QPointF(850,400));
       count_down ->setFont(font);
       scene->addItem(count_down);
    static qreal last_calc_fps_time = QTime::currentTime().msecsSinceStartOfDay(), frame_cnt = 0;
    QObject::connect(frame_timer, &QTimer::timeout, scene, [&]{
        scene->advance();
        scenario->advance();
        update_game_info();
        int flag = this->scenario->is_end();
        if(flag == 1)
        {
            game_end(1);
        }
        if(flag == -1 || player->getHp()<=0)
        {
            game_end(0);
        }
        frame_cnt++;
        if (QTime::currentTime().msecsSinceStartOfDay() - last_calc_fps_time > 1000) {
            last_calc_fps_time = QTime::currentTime().msecsSinceStartOfDay();
//            qDebug() << "fps: " << frame_cnt << endl;
            frame_cnt = 0;
        }
    });
    view->installEventFilter(kbhandler);

    view->setBackgroundBrush(QBrush(QPixmap(":/game/assets/background.jpg")));

    //        view->setFixedSize(WIDTH, HEIGHT);
    view->setFixedSize(view->sizeHint());
    view->show();


    bgm_player->setMedia(QUrl("qrc:/game/assets/sound/bgm (compressed).wav"));
    bgm_player->setVolume(BGM_VOLUME);
    bgm_player->play();
//    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setCacheMode(QGraphicsView::CacheBackground);
    continue_button = new Mypushbottom(view, true,
                                                 ":/game/assets/button.png",150);
    main_menu_button = new Mypushbottom(view, true,
                                                 ":/game/assets/button.png",150); //@TODO: button assets
   continue_button->resize(500,100);
   QPoint delta = {
       continue_button->rect().width() / 2,
       continue_button->rect().height() / 2
   };
   continue_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y());


   main_menu_button->resize(500,100);
   main_menu_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y() - 120);

   connect(continue_button, &Mypushbottom::clicked, continue_button, [&](){
       QTimer::singleShot(300, this,[&](){
           this->gameContinue();
       });
   });


   connect(main_menu_button, &Mypushbottom::clicked, main_menu_button ,[&](){
       QTimer::singleShot(300, this, [&](){
           father_widget ->show();

           view ->hide();
       });
   });

   pauseboard_widgets = std::vector<QWidget*>({continue_button, main_menu_button});

   frame_timer->start(1000 / FPS);
    //test code.
    scenario->start(this);
}

GameController::~GameController() {
    view->deleteLater();
    for (auto ep : enemyPrototypes_boss) {
        delete ep;
    }

    for (auto ep : enemyPrototypes_small) {
        delete ep;
    }
    //其余成员被Qt自动析构.
}
void GameController::update_game_info(){
    player_hp_show ->setRect(QRectF(850,600,player->getHp()/PLAYER_HP * 200,50));
    enemy_hp_show ->setRect(QRectF(850,800,scenario->get_hp_rate()*200,50));
    count_down ->setPlainText(QString::number(this->scenario->get_last_time()));
}
QGraphicsScene *GameController::getScene() const
{
    return scene;
}

bool GameController::isPaused() {
    return !frame_timer->isActive();
}

void GameController::gameContinue() {
    bgm_player->play();
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
    for (auto widget : pauseboard_widgets) {
        widget->show();
    }
}

void GameController::pause() {
    bgm_player->pause();
    frame_timer->stop();
    for (auto &pair : timers) if (pair.timer->remainingTime() > 0) {
        pair.remainingTime = pair.timer->remainingTime();
        pair.timer->stop();
    }
    this->pause_shield = scene->addRect(scene->sceneRect(), QPen(), QBrush(QColor(255,255,255,100)));
    this->showPauseboard();
}
void GameController::game_end(const bool &is_win) {
    bgm_player->pause();
    frame_timer->stop();
    for (auto &pair : timers) if (pair.timer->remainingTime() > 0) {
        pair.remainingTime = pair.timer->remainingTime();
        pair.timer->stop();
    }
    this->pause_shield = scene->addRect(scene->sceneRect(), QPen(), QBrush(QColor(255,255,255,100)));
    if(is_win)
    {
        qDebug() << "win!"<<endl;
        Mypushbottom * win_button = new Mypushbottom(view, true,
                                                     ":/game/assets/button.png",150);
       win_button->resize(500,100);
       QPoint delta = {
           win_button->rect().width() / 2,
           win_button->rect().height() / 2
       };
       win_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y());
       win_button ->show();
       connect(win_button, &Mypushbottom::clicked, win_button ,[&](){
           QTimer::singleShot(300, this, [&](){
               father_widget ->show();

               view ->hide();
           });
       });

    }
    else
    {
        qDebug() << "loss!"<<endl;
        Mypushbottom * loss_button = new Mypushbottom(view, true,
                                                     ":/game/assets/button.png",150);
       loss_button->resize(500,100);
       QPoint delta = {
           loss_button->rect().width() / 2,
           loss_button->rect().height() / 2
       };
       loss_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y());
       loss_button ->show();
       connect(loss_button, &Mypushbottom::clicked, loss_button ,[&](){
           QTimer::singleShot(300, this, [&](){
               father_widget ->show();

               view ->hide();
           });
       });
    }
}

KeyboardHandler *GameController::getKbhandler() const
{
    return kbhandler;
}
