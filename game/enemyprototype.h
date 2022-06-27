#ifndef ENEMYPROTOTYPE_H
#define ENEMYPROTOTYPE_H


#include "action.hpp"
#include "enemy.h"
#include "qpoint.h"
#include <vector>

class GameController;
//为了使用Action的多态而引出的一堆极其丑陋的代码
class EnemyPrototype
{
    std::vector<Action*>
                    actions;
    QString         picUrl;
    int             hp;

public:
    EnemyPrototype(QString picUrl = ":/game/assets/enemy.png", int hp = ENEMY_HP);

    EnemyPrototype(const EnemyPrototype &e);
    EnemyPrototype(EnemyPrototype &&e);

    EnemyPrototype& operator=(const EnemyPrototype &e);
    EnemyPrototype& operator=(EnemyPrototype &&e) = delete;

    // it takes the ownership of *action.
    EnemyPrototype& operator<<(Action *action);
    Enemy *spawnIt(GameController *gc, QPointF initLoc) const;

    ~EnemyPrototype();
    int getHp() const;
    void setHp(int newHp);
};

extern std::vector<EnemyPrototype*> enemyPrototypes;
void initEnemyPrototypes();

#endif // ENEMYPROTOTYPE_H
