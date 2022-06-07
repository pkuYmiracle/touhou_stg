#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPoint>
#include <QVector2D>

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    QVector2D speed = {0, 0}; //speed vector per frame.
public:
    explicit Entity();

    //实现位置的移动
    void    advance(int phase) override;

    bool    isPlayer() const;
    bool    isEnemy() const;
    bool    isBullet() const;
    QVector2D getSpeed() const;
    void setSpeed(QVector2D newSpeed);
};

#endif // ENTITY_H