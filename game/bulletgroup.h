#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include "bulletprototype.h"

#include <vector>




class BulletGroup
{
public:
    BulletGroup();
    std::vector<BulletPrototype> bullets;
    void spawnBullteGroupFrom(LivingEntity *e) const;


};
extern std::vector<BulletGroup> bulletGroups;
void makeBulletGroups();


#endif // BULLETGROUP_H
