#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "qdebug.h"
#include <QObject>
#include <QTimer>
#include <QString>
#include <QGraphicsTextItem> 
#include <QGraphicsRectItem>
#include <QLabel>
class Scenario;
class Player;
class QGraphicsScene;
class QGraphicsView;

class KeyboardHandler;
class GameController : public QObject {
    QGraphicsView       *view;
    QGraphicsScene      *scene;
    QTimer              *frameTimer;
    Player              *player;
    KeyboardHandler     *kbhandler;
    Scenario            *scenario;
    QGraphicsTextItem * level_name,*player_hp,*enemy_hp;
    QGraphicsRectItem * player_hp_show,*enemy_hp_show;

    std::vector<QTimer*>
                        timers;
   std::vector<QString> info;//用于从之前选项中输入这个关卡的相关信息
   void update_game_info();
public:
    explicit GameController(const std::vector<QString> &info_ls,QObject *parent = nullptr);

    ~GameController();
    KeyboardHandler *getKbhandler() const;
    QGraphicsScene  *getScene() const;

    bool isPaused();
    void pause();
    void gameContinue();

    template<class T>
    void createOneShotTimer(int interval, QObject *context, T callable) {
        auto timer = new QTimer(this);
        timer->setSingleShot(1);
        QObject::connect(timer, &QTimer::timeout, context, callable);
        timers.push_back(timer);
        timer->setInterval(interval);
        timer->start();
    }
};

#endif












