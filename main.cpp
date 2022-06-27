#include "baseboard.h"
#include"startboard.h"
#include <QApplication>
#include "game/gamecontroller.h"
#include <QDebug>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Startboard w;
//    w.show();
    std::vector<QString> lis;
    lis.push_back(QString("first_level"));
    GameController gc(lis);
    return a.exec();
}
