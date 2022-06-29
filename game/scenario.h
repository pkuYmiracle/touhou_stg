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
    QVector<Enemy*> enemies,bosses,smalles;
    QVector<qreal>boss_hpes;
    int boss_number;
    //((time, loc), ep)
public:
    Scenario();

    //time for secs.
    Scenario&   add(qreal time, QPointF loc, EnemyPrototype &ep);
    bool        isCompleted() const;
    void        start(GameController *gc);
    static Scenario  gen_random_scenario();
    bool is_end() const;
    qreal get_hp_rate() const;
};
extern std::vector<Scenario> scenarios;
void init_scenarios();
#endif // SCENARIO_H
