#ifndef KEYBOARDHANDLER_HPP
#define KEYBOARDHANDLER_HPP

#include "qnamespace.h"
#include <QObject>
#include <set>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QMouseEvent>
class KeyboardHandler : public QObject
{
    std::set<int> pressedKeys;
public:
    explicit KeyboardHandler(QObject *parent)
        : QObject(parent)
    {

    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) {

        //for developer to conveniently locate.
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *e = dynamic_cast<QMouseEvent*>(event);
            qDebug() << e->pos() << endl;
            return true;
        }

        if (event->type() == QEvent::KeyPress ||
            event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyevent = dynamic_cast<QKeyEvent*>(event);
//            if (!keyevent->isAutoRepeat()) {
                if (event->type() == QEvent::KeyPress) {
                    pressedKeys.insert(keyevent->key());
                } else{
                    if (pressedKeys.count(keyevent->key()))
                        pressedKeys.erase(keyevent->key());
                }
//            }
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
    }

public:
    bool isKeyPressed(Qt::Key key) {
        return pressedKeys.count(key);
    }

};

#endif // KEYBOARDHANDLER_HPP
