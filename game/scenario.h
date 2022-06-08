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
    //the last one is boss
    //when boss die, the scenario is completed.
public:
    Scenario();

    //time for secs.
    Scenario&   add(qreal time, QPointF loc, EnemyPrototype &ep);
    void        start(QGraphicsScene *scene);
    bool        isCompleted() const;
};

extern std::vector<Scenario> scenarios;
void makeScenarios();
#endif // SCENARIO_H
