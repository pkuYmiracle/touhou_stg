#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <cassert>
#include <QPaintEngine>
#include "game/bulletgroup.h"
#include "game/config.h"
#include "game/enemy.h"
#include "game/keyboardhandler.hpp"
#include "game/player.h"
#include "qobjectdefs.h"
#include "game/enemyprototype.h"

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
        makeBulletGroups();
        makeEnemyPrototypes();
        QRect sceneRect = QRect(0, 0, WIDTH, HEIGHT);
        view->setScene(scene);
        player->setPos(sceneRect.center());
        scene->setSceneRect(sceneRect);
        QObject::connect(frameTimer, SIGNAL(timeout()), scene, SLOT(advance()));
        view->installEventFilter(kbhandler);
        scene->addItem(player);
        view->setBackgroundBrush(QBrush(QPixmap(":/game/assets/background.jpg")));

//        view->setFixedSize(WIDTH, HEIGHT);
        view->setFixedSize(view->sizeHint());
        view->show();
        frameTimer->start(1000 / FPS);

        enemyPrototype.front()->spawnIt(scene, sceneRect.center());
    }

    ~GameController() {
        view->deleteLater();
        for (auto ep : enemyPrototype) {
            delete ep;
        }
        //其余成员被Qt自动析构.
    }
    KeyboardHandler *getKbhandler() const;
    QGraphicsScene  *getScene() const;
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
