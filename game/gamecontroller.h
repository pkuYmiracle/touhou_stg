#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QObject>
#include <QSound>
#include <QTimer>

#include "level_menu.h"
#include "mypushbutton.h"
#include "qdebug.h"

class BulletGroup;
class Scenario;
class Player;
class QGraphicsScene;
class QGraphicsView;

class KeyboardHandler;
class GameController : public QObject {
    Level_menu *father_widget;
    QGraphicsView *view;
    QGraphicsScene *scene;
    ///
    /// \brief frame_timer 逐帧定时器
    ///
    QTimer *frame_timer;
    Player *player;
    KeyboardHandler *kbhandler;
    ///
    /// \brief scenario 关卡管理器
    ///
    Scenario *scenario;
    QGraphicsTextItem *level_name, *player_hp, *enemy_hp, *last_time_count,
        *count_down, *remain_boss_counts, *esc_stop;
    QGraphicsRectItem *player_hp_show, *enemy_hp_show;
    Mypushbutton *continue_button, *main_menu_button, *help_button;
    struct Timer {
        QTimer *timer;
        int remainingTime;  // if paused.
    };
    ///
    /// \brief timers 所有正在运行的oneShotTimer，用于实现暂停
    ///
    std::vector<Timer> timers;
    QGraphicsItem *pause_shield;
    std::vector<QString> info;  //用于从之前选项中输入这个关卡的相关信息
    std::vector<QWidget *> pauseboard_widgets;
    QMediaPlayer *bgm_player;
    ///
    /// \brief update_game_info 侧边栏更新
    ///
    void update_game_info();
    void init_scenario();
    ///
    /// \brief game_end 终止游戏
    /// \param is_win
    ///
    void game_end(const int &is_win);

    void initSidebar();

public:
    explicit GameController(const std::vector<QString> &info_ls,
                            Level_menu *from, BulletGroup *player_bullet,
                            QObject *parent = nullptr);

    ~GameController();
    KeyboardHandler *getKbhandler() const;
    QGraphicsScene *getScene() const;

    bool isPaused();
    void pause();
    void gameContinue();

    ///
    /// \brief createOneShotTimer 创建受暂停控制的一次性计时器
    /// \param interval
    /// \param context
    /// \param callable
    ///
    template <class T>
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
