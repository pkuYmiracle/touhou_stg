#include "gamecontroller.h"
#include "baseboard.h"
#include "game/bulletgroup.h"
#include "game/enemyprototype.h"
#include "game/scenario.h"
#include "keyboardhandler.hpp"
#include "mypushbutton.h"
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
            this ->scenario = new Scenario (scenarios[id]);
    else
        this ->scenario = new Scenario (Scenario:: gen_random_scenario());
    this->scenario->print_boss();
}

GameController::GameController(const std::vector<QString> &info_ls, Level_menu * from, BulletGroup *player_bullet, QObject *parent):
    QObject(parent),
    father_widget(from),
    view(new QGraphicsView()),
    scene(new QGraphicsScene(this)),
    frame_timer(new QTimer(this)),
    player(new Player(this,info_ls[2])),
    kbhandler(new KeyboardHandler(this)),
    level_name(new QGraphicsTextItem),
    last_time_count(new QGraphicsTextItem),
    count_down(new QGraphicsTextItem),
    remain_boss_counts(new QGraphicsTextItem),
    esc_stop(new QGraphicsTextItem),
    player_hp_show(new QGraphicsRectItem),
    enemy_hp_show(new QGraphicsRectItem),
    info(info_ls),
    bgm_player(new QMediaPlayer)
{
    player->setBulletGroup(player_bullet);
    QRect sceneRect = QRect(0, 0, WIDTH, HEIGHT);
    view->setScene(scene);
//    view->setWindowFlag(Qt::FramelessWindowHint);
    player->setPos(GAME_BOARD_RECT.center().x() + 100,GAME_BOARD_RECT.center().y() + 200);
    scene->setSceneRect(sceneRect);

    scene->addItem(player);

    this->initSidebar();
    static qreal last_calc_fps_time = QTime::currentTime().msecsSinceStartOfDay(), frame_cnt = 0;
    QObject::connect(frame_timer, &QTimer::timeout, scene, [&]{
        if(player->getHp()<=0)
        {
                    game_end(0);
        }
        scene->advance();

        if(player->getHp()<=0)
        {
                    game_end(0);
        }
        scenario->advance();

        if(player->getHp()<=0)
        {
                    game_end(0);
        }
        update_game_info();
        int flag = this->scenario->is_end();
        if(flag == 1)
        {
            game_end(1);
        }
        if(flag == -1)
        {
            game_end(0);
        }
        if(player->getHp()<=0)
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
    continue_button = new Mypushbutton(view, true,
                                                 ":/game/assets/continue.png",150);
    main_menu_button = new Mypushbutton(view, true,
                                                 ":/game/assets/backmain.png",150);

    help_button = new Mypushbutton(view, false,
                                                 ":/game/assets/help.png",150);
    help_button->resize(500,400);

    QPoint delta = {
        help_button->rect().width() / 2,
        help_button->rect().height() / 2
    };

    help_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y()-120);
   continue_button->resize(500,100);
   continue_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y()+300);


   main_menu_button->resize(500,100);
   main_menu_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y() +420);

   connect(continue_button, &Mypushbutton::clicked, continue_button, [&](){
       QTimer::singleShot(300, this,[&](){
           this->gameContinue();
       });
   });


   connect(main_menu_button, &Mypushbutton::clicked, main_menu_button ,[&](){
       QTimer::singleShot(300, this, [&](){
           father_widget ->show();

           view ->hide();
       });
   });

   pauseboard_widgets = std::vector<QWidget*>({continue_button, main_menu_button,help_button});
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
Scenario *GameController::getScenario() const
{
    return scenario;
}

void GameController::update_game_info(){
    qreal cur_hp= fmax(0,player->getHp());
    player_hp_show ->setRect(QRectF(915,600,cur_hp/PLAYER_HP * 200,50));
    enemy_hp_show ->setRect(QRectF(915,750,scenario->get_hp_rate()*200,50));
    count_down ->setPlainText(QString::number(this->scenario->get_last_time()/100));
    remain_boss_counts ->setPlainText(QString::number(this->scenario->remain_boss_count())+" boss left");

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
    for (auto &pair : timers) if (pair.remainingTime > 0) {
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
        Mypushbutton * win_button = new Mypushbutton(view, false,
                                                     ":/game/assets/win.png",150);
       win_button->resize(500,100);
       QPoint delta = {
           win_button->rect().width() / 2,
           win_button->rect().height() / 2
       };
       win_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y() - 100);
       win_button ->show();
        Mypushbutton * back_button = new Mypushbutton(view, true,
                                                     ":/backboard/back.png",150);
        back_button->resize(250,200);
        back_button->move(view->width() / 2 - delta.x()+60, view->height() / 2 - delta.y() + 50);
       back_button ->show();
       connect(back_button, &Mypushbutton::clicked, back_button ,[&](){
           QTimer::singleShot(300, this, [&](){
               father_widget ->show();

               view ->hide();
           });
       });

    }
    else
    {
        qDebug() << "loss!"<<endl;
        Mypushbutton * lose_button = new Mypushbutton(view, false,
                                                     ":/game/assets/die.png",150);
       lose_button->resize(500,100);
       QPoint delta = {
           lose_button->rect().width() / 2,
           lose_button->rect().height() / 2
       };
       lose_button->move(view->width() / 2 - delta.x(), view->height() / 2 - delta.y() - 100);
       lose_button ->show();
        Mypushbutton * back_button = new Mypushbutton(view, true,
                                                     ":/backboard/back.png",150);
       back_button->resize(250,200);
       back_button->move(view->width() / 2 - delta.x()+60, view->height() / 2 - delta.y() + 50);
       back_button ->show();
       connect(back_button, &Mypushbutton::clicked, back_button ,[&](){
           QTimer::singleShot(300, this, [&](){
               father_widget ->show();

               view ->hide();
           });
       });
    }
}

void GameController::initSidebar()
{
    scene->addRect(QRect(QPoint(850,0), QPoint(1200,1000)), QPen(), QBrush(QColor(0,0,0,255)));

//    auto sidebar_background = scene->addPixmap(QPixmap(":/game/assets/sidebar.jpg"));
//    sidebar_background->setPos(830, 0);

    level_name ->setPlainText(info[0]);
    level_name ->setPos(QPointF(900,100));
    QFont font("Helvetica");
    font.setPointSize(25);
    level_name->setDefaultTextColor(QColor(255,255,255));
    level_name ->setFont(font);
    scene->addItem(level_name);

    last_time_count ->setPlainText("Countdown");
    last_time_count ->setPos(QPointF(900,300));
    last_time_count->setDefaultTextColor(QColor(255,255,255));
    last_time_count ->setFont(font);
    scene->addItem(last_time_count);

    auto player_hp = scene->addPixmap(QPixmap(":/game/assets/playerhp.png"));
    player_hp->setScale(0.5);
    player_hp->setPos(QPointF(900,530));
    scene->addItem(player_hp);

    auto enemy_hp = scene->addPixmap(QPixmap(":/game/assets/enemyhp.png"));
    enemy_hp->setScale(0.5);
    enemy_hp->setPos(QPointF(900,700));
    scene->addItem(enemy_hp);

    player_hp_show ->setBrush(QBrush(QColor(0,150,0)));
    player_hp_show ->setRect(QRectF(900,600,200,30));
    scene->addItem(player_hp_show);

    enemy_hp_show ->setBrush(QBrush(QColor(200,0,0)));
    enemy_hp_show ->setRect(QRectF(900,750,200,30));
    scene->addItem(enemy_hp_show);
    init_scenario();
    count_down ->setPlainText(QString::number(this->scenario->get_last_time()/100));
    count_down ->setPos(QPointF(940,400));
    count_down ->setFont(font);
    count_down->setDefaultTextColor(QColor(255,255,255));
    scene->addItem(count_down);

    esc_stop ->setPlainText("按Esc键暂停");
    esc_stop ->setPos(QPointF(900,850));
    esc_stop->setDefaultTextColor(QColor(255,255,255));
    esc_stop ->setFont(font);
    scene->addItem(esc_stop);

    remain_boss_counts ->setPlainText(QString::number(this->scenario->remain_boss_count())+" boss left");
    remain_boss_counts ->setPos(QPointF(880,200));
    remain_boss_counts ->setFont(font);
    remain_boss_counts->setDefaultTextColor(QColor(255,255,255));
    scene->addItem(remain_boss_counts);
}

KeyboardHandler *GameController::getKbhandler() const
{
    return kbhandler;
}
