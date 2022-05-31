#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPoint>

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    QPointF speed = {0, 0}; //speed vector per frame.
public:
    explicit Entity();

    //实现位置的移动
    void    advance(int phase) override;


    QPointF getSpeed() const;
    void setSpeed(QPointF newSpeed);
};

#endif // ENTITY_H
