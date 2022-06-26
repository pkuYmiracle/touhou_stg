#include "gamecontroller.h"


GameController::GameController(QObject *parent) :
    QObject(parent),
    view(new QGraphicsView()),
    scene(new QGraphicsScene(this)),
    frameTimer(new QTimer(this)),
    player(new Player(this)),
    kbhandler(new KeyboardHandler(this))
{
    initBulletGroups();
    initEnemyPrototypes();
    initScenarios();

    QRect sceneRect = QRect(0, 0, WIDTH, HEIGHT);
    view->setScene(scene);
    player->setPos(sceneRect.center());
    scene->setSceneRect(sceneRect);
    scenario = new Scenario(scenarios[0]); // it can only copy before start.
    QObject::connect(frameTimer, &QTimer::timeout, scene, [=]{
        scene->advance();
    });
    view->installEventFilter(kbhandler);
    scene->addItem(player);
    view->setBackgroundBrush(QBrush(QPixmap(":/game/assets/background.jpg")));

    //        view->setFixedSize(WIDTH, HEIGHT);
    view->setFixedSize(view->sizeHint());
    view->show();
    frameTimer->start(1000 / FPS);

    //test code.
    scenario->start(scene);
    //        qDebug() << player->offset() << endl;
    //        player->setOffset(player->boundingRect().width() / 2, player->boundingRect().height() / 2);
}

GameController::~GameController() {
    view->deleteLater();
    for (auto ep : enemyPrototypes) {
        delete ep;
    }
    //其余成员被Qt自动析构.
}

QGraphicsScene *GameController::getScene() const
{
    return scene;
}

bool GameController::is_paused() {
    return frameTimer->isActive();
}

void GameController::game_continue() {
    frameTimer->start();
}

void GameController::pause() {
    frameTimer->stop();
}

KeyboardHandler *GameController::getKbhandler() const
{
    return kbhandler;
}
