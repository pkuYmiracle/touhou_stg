#ifndef LIVINGENTITY_H
#define LIVINGENTITY_H

#include "game/entity.h"
#include <QObject>

class LivingEntity : public Entity
{
    float hp; //short for health point

public:
    explicit LivingEntity();

//    处理子弹和生物的碰撞
    void advance(int phase) override;


    float getHp() const;
    void setHp(float newHp);
};

#endif // LIVINGENTITY_H
