#ifndef ACTION_HPP
#define ACTION_HPP

#include <QPointF>

#include "bulletgroup.h"
#include "qdebug.h"
#include "qglobal.h"
class Action {
    qreal duration;  // in secs.
public:
    Action(qreal _dur) : duration(_dur) {}
    virtual ~Action() {}

    bool isMove() const;
    bool isAttack() const;
    qreal getDuration() const;

    //返回一个深拷贝，保留多态类型.
    virtual Action *clone() const = 0;
};

class Move : public Action {
    QVector2D speed;

public:
    Move(QPointF _speed, qreal _dur) : Action(_dur), speed(_speed) {}
    const QVector2D &getSpeed() const;
    Move *clone() const;
};

class Attack : public Action {
    BulletGroup bg;

public:
    Attack(BulletGroup bg, qreal _dur) : Action(_dur), bg(bg) {}
    const BulletGroup &getBulletGroup() const;
    Attack *clone() const;
};

inline bool Action::isMove() const {
    return dynamic_cast<const Move *>(this) != 0;
}

inline bool Action::isAttack() const {
    return dynamic_cast<const Attack *>(this) != 0;
}

inline qreal Action::getDuration() const { return duration; }

inline const BulletGroup &Attack::getBulletGroup() const { return bg; }

inline Attack *Attack::clone() const { return new Attack(*this); }

inline const QVector2D &Move::getSpeed() const { return speed; }

inline Move *Move::clone() const { return new Move(*this); }
#endif  // ACTION_HPP
