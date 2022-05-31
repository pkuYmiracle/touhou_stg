#include "livingentity.h"

float LivingEntity::getHp() const
{
    return hp;
}

void LivingEntity::setHp(float newHp)
{
    hp = newHp;
}

LivingEntity::LivingEntity()
{

}

void LivingEntity::advance(int phase)
{
    if (phase == 1) return;
    Entity::advance(phase);
}
