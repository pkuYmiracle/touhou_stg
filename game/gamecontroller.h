#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "qdebug.h"
#include <QObject>
#include <QTimer>

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
    std::vector<QTimer*>
                        timers;
public:
    explicit GameController(QObject *parent = nullptr);

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












