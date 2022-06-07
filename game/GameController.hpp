#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <cassert>
#include <QPaintEngine>
#include "game/config.h"
#include "game/enemy.h"
#include "game/keyboardhandler.hpp"
#include "game/player.h"
#include "qobjectdefs.h"

class GameController : public QObject {
    QGraphicsView       *view;
    QGraphicsScene      *scene;
    QTimer              *frameTimer;
    Player              *player;
    KeyboardHandler     *kbhandler;
public:
    explicit GameController(QObject *parent = nullptr) :
        QObject(parent),
        view(new QGraphicsView()),
        scene(new QGraphicsScene(this)),
        frameTimer(new QTimer(this)),
        player(new Player(this)),
        kbhandler(new KeyboardHandler(this))
    {
        view->setFixedSize(WIDTH, HEIGHT);

        QRect sceneRect = QRect(5, 5, WIDTH - 5, HEIGHT - 5);
        view->setScene(scene);
        player->setPos(sceneRect.center());
        scene->setSceneRect(sceneRect);
        QObject::connect(frameTimer, SIGNAL(timeout()), scene, SLOT(advance()));
        view->installEventFilter(kbhandler);
        scene->addItem(player);
        view->setBackgroundBrush(QBrush(QPixmap(":/game/assets/background.jpg")));
        view->show();
        frameTimer->start(1000 / FPS);




        //for test
        Enemy *e = new Enemy();
        e->setPos(sceneRect.center() - QPointF(100, 100));
        scene->addItem(e);
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

#endif  //GAMECONTROLLER_HPP
