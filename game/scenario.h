#ifndef SCENARIO_H
#define SCENARIO_H

#include <qtimer.h>

#include <vector>

#include "game/enemyprototype.h"
#include "qgraphicsscene.h"
#include "qpair.h"

class Scenario {
    // dont learn me.
    QVector<QPair<QPair<qreal, QPointF>, EnemyPrototype>> enemySpawnConfig;
    QVector<Enemy *> bosses, smalles;
    QVector<qreal> boss_hpes;
    int boss_number;
    bool is_lose() const;
    bool is_win() const;
    //((time, loc), ep)
public:
    Scenario();
    int boss_id;               //记录目前是第多少个boss
    QVector<qreal> boss_time;  //记录boss出现的时间
    qreal countdown;
    // time for secs.
    Scenario &add(qreal time, QPointF loc, const EnemyPrototype &ep);
    void start(GameController *gc);
    static Scenario gen_random_scenario();
    int is_end() const;
    qreal get_hp_rate() const;
    void print_boss() const;      //用于测试
    qreal get_last_time() const;  //显示倒计时
    void advance();
    int remain_boss_count() const;
};
extern std::vector<Scenario> scenarios;
void init_scenarios();
#endif  // SCENARIO_H
