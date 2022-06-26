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
#include "game/scenario.h"
#include "qobjectdefs.h"
#include "game/enemyprototype.h"

class GameController : public QObject {
    QGraphicsView       *view;
    QGraphicsScene      *scene;
    QTimer              *frameTimer;
    Player              *player;
    KeyboardHandler     *kbhandler;
    Scenario            *scenario;
public:
    explicit GameController(QObject *parent = nullptr);

    ~GameController();
    KeyboardHandler *getKbhandler() const;
    QGraphicsScene  *getScene() const;

    bool is_paused();
    void pause();
    void game_continue();
};













