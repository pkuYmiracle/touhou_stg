#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "qdebug.h"
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QObject>
#include <QSound>
#include <QTimer>
#include "level_menu.h"
#include "mypushbottom.h"

class Scenario;
class Player;
class QGraphicsScene;
class QGraphicsView;

class KeyboardHandler;
class GameController : public QObject {
    Level_menu * father_widget;
    QGraphicsView       *view;
    QGraphicsScene      *scene;
    QTimer              *frame_timer;
    Player              *player;
    KeyboardHandler     *kbhandler;
    Scenario            *scenario;
    QGraphicsTextItem   *level_name,
                        *player_hp,
                        *enemy_hp,
                        *last_time_count,
                        *count_down,
                        *remain_boss_counts,
                        *esc_stop;
    QGraphicsRectItem   *player_hp_show,
                        *enemy_hp_show;
    Mypushbottom *continue_button,*main_menu_button,*help_button;
    struct Timer{
        QTimer* timer;
        int     remainingTime; // if paused.
    };
    std::vector<Timer>  timers;
    QGraphicsItem       *pause_shield;
    std::vector<QString>
                        info;//用于从之前选项中输入这个关卡的相关信息
    std::vector<QWidget*>
                        pauseboard_widgets;
    QMediaPlayer            *bgm_player;
    void                update_game_info();
    void init_scenario();
    void game_end(const bool &is_win);
    void initSidebar();
public:
    explicit GameController(const std::vector<QString> &info_ls,Level_menu * from,QObject *parent = nullptr);

    ~GameController();
    KeyboardHandler *getKbhandler() const;
    QGraphicsScene  *getScene() const;

    bool isPaused();
    void pause();
    void gameContinue();

    // 此处创建的OneShotTimer会被暂停控制
    template<class T>
    void createOneShotTimer(int interval, QObject *context, T callable) {
        auto timer = new QTimer(this);
        timer->setSingleShot(1);
        QObject::connect(timer, &QTimer::timeout, context, callable);
        timers.push_back({timer, /*remaining time*/ 0});
        timer->setInterval(interval);
        timer->start();
    }


    void showPauseboard();

    Scenario *getScenario() const;
};

#endif












