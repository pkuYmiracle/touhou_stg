#ifndef BULLETGROUP_H
#define BULLETGROUP_H

#include <vector>

#include "bulletprototype.h"

class BulletGroup {
public:
    BulletGroup();
    std::vector<BulletPrototype> bullets;

    ///
    /// \brief spawnBulletGroupFrom 令e发射该BulletGroup
    /// \param e
    ///
    void spawnBulletGroupFrom(LivingEntity *e) const;
};
extern std::vector<BulletGroup> bulletGroups;


///
/// \brief initBulletGroups 计算预制的BulletGroup
///
void initBulletGroups();

#endif  // BULLETGROUP_H
