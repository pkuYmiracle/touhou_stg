#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include "bulletprototype.h"

#include <vector>




class BulletGroup
{
public:
    BulletGroup();
    std::vector<BulletPrototype> bullets;
    void spawnBulletGroupFrom(LivingEntity *e) const;


};
extern std::vector<BulletGroup> bulletGroups;
void initBulletGroups();


#endif // BULLETGROUP_H
