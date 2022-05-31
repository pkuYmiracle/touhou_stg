#ifndef BONUS_H
#define BONUS_H

#include "entity.h"
#include <QObject>

class Bonus : public Entity
{
    Q_OBJECT
public:
    explicit Bonus(QObject *parent);
};

#endif // BONUS_H
