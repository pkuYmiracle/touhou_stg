#ifndef ENEMYPROTOTYPE_H
#define ENEMYPROTOTYPE_H


#include "action.hpp"
#include "enemy.h"
#include "qpoint.h"
#include <vector>

class EnemyPrototype
{
    std::vector<Action*>
                    actions;
    QString         picUrl;

public:
    EnemyPrototype(QString picUrl = ":/game/assets/enemy.png");

    // a terrible impl.
    EnemyPrototype& operator>>(Action *action);
    Enemy*          spawnIt(QGraphicsScene *scene, QPointF initLoc);

    ~EnemyPrototype();
};

extern std::vector<EnemyPrototype*> enemyPrototypes;
void makeEnemyPrototypes();

#endif // ENEMYPROTOTYPE_H
