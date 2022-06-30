#ifndef ENEMYPROTOTYPE_H
#define ENEMYPROTOTYPE_H

#include <vector>

#include "action.hpp"
#include "enemy.h"
#include "qpoint.h"

class GameController;
//为了使用Action的多态而引出的一堆极其丑陋的代码
class EnemyPrototype {
    std::vector<Action *> actions;
    QString picUrl;
    int hp;

public:
    bool is_boss;
    EnemyPrototype(QString picUrl = ":/game/assets/enemy.png",
                   int hp = ENEMY_HP, bool isboss = 0);

    EnemyPrototype(const EnemyPrototype &e);
    EnemyPrototype(EnemyPrototype &&e);

    EnemyPrototype &operator=(const EnemyPrototype &e);
    EnemyPrototype &operator=(EnemyPrototype &&e) = delete;

    // it takes the ownership of *action.
    EnemyPrototype &operator<<(Action *action);
    Enemy *spawnIt(GameController *gc, QPointF initLoc) const;

    ~EnemyPrototype();
    int getHp() const;
    void setHp(int newHp);
};

extern std::vector<EnemyPrototype *> enemyPrototypes_boss,
    enemyPrototypes_small;
void initEnemyPrototypes();
void init_boss();
void init_small();

#endif  // ENEMYPROTOTYPE_H
