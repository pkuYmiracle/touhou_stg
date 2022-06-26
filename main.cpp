#include "baseboard.h"
#include"startboard.h"
#include <QApplication>
#include "game/gamecontroller.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Startboard w;
//    w.show();

    GameController gc;
    return a.exec();
}
