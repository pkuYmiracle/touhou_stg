#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <cassert>

#include "game/config.h"
#include "game/keyboardhandler.hpp"
#include "game/player.h"

class GameController : public QObject {
    QGraphicsView       *view;
    QGraphicsScene      *scene;
    QTimer              *frame_timer;
    Player              *player;
    KeyboardHandler     *kbhandler;
public:
    explicit GameController(QObject *parent) :
        QObject(parent),
        view(new QGraphicsView()),
        scene(new QGraphicsScene(this)),
        frame_timer(new QTimer(this)),
        player(new Player(this)),
        kbhandler(new KeyboardHandler(this))
    {
        assert(parent != NULL);
        view->setScene(scene);
        scene->setSceneRect(0, 0, WIDTH, HEIGHT);
        view->setFixedSize(WIDTH, HEIGHT);
        QObject::connect(frame_timer, SIGNAL(timeout()), scene, SLOT(advance()));
        view->installEventFilter(kbhandler);
        frame_timer->start(1000 / FPS);
        scene->addItem(player);
        view->show();
    }

    ~GameController() {
        view->deleteLater();
        //其余成员是自己的子对象，被Qt自动析构.
    }
};

#endif  //GAMECONTROLLER_H
