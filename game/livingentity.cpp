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
