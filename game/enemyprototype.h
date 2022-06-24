#ifndef ENEMYPROTOTYPE_H
#define ENEMYPROTOTYPE_H


#include "action.hpp"
#include "enemy.h"
#include "qpoint.h"
#include <vector>

//为了使用Action的多态而引出的一堆极其丑陋的代码
class EnemyPrototype
{
    std::vector<Action*>
                    actions;
    QString         picUrl;

public:
    EnemyPrototype(QString picUrl = ":/game/assets/enemy.png");

    EnemyPrototype(const EnemyPrototype &e);
    EnemyPrototype(EnemyPrototype &&e);

    EnemyPrototype& operator=(const EnemyPrototype &e);
    EnemyPrototype& operator=(EnemyPrototype &&e) = delete;

    // it takes the ownership of *action.
    EnemyPrototype& operator<<(Action *action);
    Enemy*          spawnIt(QGraphicsScene *scene, QPointF initLoc) const;

    ~EnemyPrototype();
};

extern std::vector<EnemyPrototype*> enemyPrototypes;
void initEnemyPrototypes();

#endif // ENEMYPROTOTYPE_H
