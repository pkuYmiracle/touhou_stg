#ifndef ENEMYPROTOTYPE_H
#define ENEMYPROTOTYPE_H

#include <vector>

#include "action.hpp"
#include "enemy.h"
#include "qpoint.h"

class GameController;
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

    ///
    /// \brief operator << 为该原型添加一个动作
    /// \param action
    /// \return self
    /// \attention it takes the ownership of *action.
    ///
    EnemyPrototype &operator<<(Action *action);

    ///
    /// \brief spawnIt 在给定的初始位置实例化该EnemyPrototype
    /// \param gc GameController实例
    /// \param initLoc 初始位置
    /// \return 指向Enemy实例的指针
    ///
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
