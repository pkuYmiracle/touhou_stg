#ifndef KEYBOARDHANDLER_HPP
#define KEYBOARDHANDLER_HPP

#include "qnamespace.h"
#include <QObject>
#include <set>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

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
        if (event->type() == QEvent::KeyPress ||
            event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyevent = dynamic_cast<QKeyEvent*>(event);
            if (!keyevent->isAutoRepeat()) {
                if (!pressedKeys.insert(keyevent->key()).second) { //已经存在
                    pressedKeys.erase(keyevent->key());
                }
            }
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
