#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPoint>
#include <QVector2D>

#include "qpixmap.h"

class Entity : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
protected:
    /// 每帧的速度
    QVector2D speed = {0, 0};
public:
    explicit Entity();
    virtual ~Entity(){};

    /// 逐帧调用，实现位置移动
    void advance(int phase) override;

    bool isPlayer() const;
    bool isEnemy() const;
    bool isBullet() const;
    QVector2D getSpeed() const;
    void setSpeed(QVector2D newSpeed);

    void setPixmap(const QPixmap &pixmap);
};

#endif  // ENTITY_H
