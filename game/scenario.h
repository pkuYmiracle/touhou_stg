#ifndef SCENARIO_H
#define SCENARIO_H


#include "game/enemyprototype.h"
#include "qgraphicsscene.h"
#include "qpair.h"
#include <qtimer.h>
#include <vector>

class Scenario
{
    //dont learn me.
    QVector<QPair<QPair<qreal, QPointF>, EnemyPrototype>> enemySpawnConfig;
    QVector<Enemy*> enemies;
    //((time, loc), ep)
public:
    Scenario();

    //time for secs.
    Scenario&   add(qreal time, QPointF loc, EnemyPrototype &ep);
    bool        isCompleted() const;
    void        start(GameController *gc);
};

extern std::vector<Scenario> scenarios;
void initScenarios();
#endif // SCENARIO_H
