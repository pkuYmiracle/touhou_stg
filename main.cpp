#include "baseboard.h"
#include"startboard.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Startboard w;
    w.show();
    return a.exec();
}
