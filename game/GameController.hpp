#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <cassert>
#include <QPaintEngine>
#include "game/config.h"
#include "game/keyboardhandler.hpp"
#include "game/player.h"
#include "qobjectdefs.h"

class GameController : public QObject {
    QGraphicsView       *view;
    QGraphicsScene      *scene;
    QTimer              *frame_timer;
    Player              *player;
    KeyboardHandler     *kbhandler;
public:
    explicit GameController(QObject *parent = nullptr) :
        QObject(parent),
        view(new QGraphicsView()),
        scene(new QGraphicsScene(this)),
        frame_timer(new QTimer(this)),
        player(new Player(this)),
        kbhandler(new KeyboardHandler(this))
    {
        view->setFixedSize(WIDTH, HEIGHT);

        QRect sceneRect = QRect(50, 50, WIDTH - 50, HEIGHT - 50);
        view->setScene(scene);
        player->setPos(sceneRect.center());
        scene->setSceneRect(sceneRect);
        QObject::connect(frame_timer, SIGNAL(timeout()), scene, SLOT(advance()));
        view->installEventFilter(kbhandler);
        scene->addItem(player);
        scene->setBackgroundBrush(QBrush(QPixmap(":/backboard/2.jpg")));
        view->show();
        frame_timer->start(1000 / FPS);

//        view->paintEngine()->drawLines(new QLine(0,0,500,500), 1);
    }

    ~GameController() {
        view->deleteLater();
        //其余成员是自己的子对象，被Qt自动析构.
    }
    KeyboardHandler *getKbhandler() const;
    QGraphicsScene *getScene() const;
};

inline QGraphicsScene *GameController::getScene() const
{
    return scene;
}

inline KeyboardHandler *GameController::getKbhandler() const
{
    return kbhandler;
}

#endif  //GAMECONTROLLER_H
