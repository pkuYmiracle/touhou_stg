#ifndef STARTBOARD_H
#define STARTBOARD_H

#include <QMainWindow>

#include "baseboard.h"
#include "select_level.h"

class Startboard : public Baseboard {
    Q_OBJECT
public:
    explicit Startboard(QWidget *parent = nullptr);

private:
    Select_level level_scene;
signals:
};

#endif  // STARTBOARD_H
