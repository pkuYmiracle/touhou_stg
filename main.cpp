#include <QApplication>
#include <QDebug>
#include <QString>

#include "baseboard.h"
#include "game/bulletgroup.h"
#include "game/enemyprototype.h"
#include "game/gamecontroller.h"
#include "game/scenario.h"
#include "startboard.h"
void init_work() {
    initBulletGroups();
    initEnemyPrototypes();
    init_scenarios();
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    init_work();  // 用于初始化一些信息，比如生成子弹模板，小怪orboss模板之类的。
    Startboard w;
    w.show();
    /*
    std::vector<QString> lis;
    lis.push_back(QString("first_level"));
    GameController gc(lis);
    */
    return a.exec();
}
