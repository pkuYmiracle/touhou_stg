#include "scenario.h"

#include "game/config.h"
#include "game/enemy.h"
#include "game/gamecontroller.h"
#include "qdebug.h"
#include "qtimer.h"

Scenario::Scenario() : enemySpawnConfig(), boss_number(0), boss_id(0) {}

// loc: 生成的初始位置
// ep:  使用的EnemyPrototypes
Scenario &Scenario::add(qreal time, QPointF loc, const EnemyPrototype &ep) {
    // qDebug()<<ep.is_boss<<endl;
    enemySpawnConfig.push_back({{time, loc}, ep});
    if (ep.is_boss) boss_time.push_back(time);
    return *this;
}

void Scenario::start(GameController *gc) {
    qDebug() << "Scenario::start" << bosses.size() << ' '
             << enemySpawnConfig.size() << endl;
    boss_number = 0;
    for (int i = 0; i < enemySpawnConfig.size(); i++) {
        const auto &p = enemySpawnConfig[i];
        if (p.second.is_boss == 1) {
            boss_number++;
            gc->createOneShotTimer(
                p.first.first * 1000, gc, [cnt = p, gc, this] {
                    bosses.push_back(cnt.second.spawnIt(gc, cnt.first.second));
                    boss_hpes.push_back(bosses.back()->getHp());
                });
        } else {
            gc->createOneShotTimer(p.first.first * 1000, gc,
                                   [cnt = p, gc, this] {
                                       cnt.second.spawnIt(gc, cnt.first.second);
                                   });
        }
    }
    qDebug() << "boss time :" << ' ';
    for (auto p : boss_time) qDebug() << p << ' ';
    qDebug() << endl;
    if (bosses.size()) {
        boss_id = 0;
        if (boss_id + 1 < boss_time.size()) {
            countdown = (boss_time[boss_id + 1] - boss_time[boss_id]) * 200;
            qDebug() << "QAQ一开始:" << countdown << endl;
        } else
            countdown = 2500 ;
    } else {
        countdown = 2500 ;
        boss_id = -1;
    }
}

Scenario Scenario::gen_random_scenario() {
    Scenario s2;
    double clk = 0;
    for (int boss_count = 1; boss_count <= 7; boss_count++) {
        int id = rand() % enemyPrototypes_boss.size();
        int x = rand() % 400 + 50, y = rand() % 400 + 50;
        s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_boss[id]);
        //接下来是小怪
        for (int i = 0; i < 10; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 9; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 9; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5 + 8;
    }
    return s2;
}
std::vector<Scenario> scenarios;
void init_scenarios() {
    Scenario s1;
    double clk = 0;
    for (int boss_count = 1; boss_count <= 2; boss_count++) {
        int id = rand() % enemyPrototypes_boss.size();
        int x = rand() % 400 + 50, y = rand() % 400 + 50;
        s1.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_boss[id]);
        //接下来是小怪
        for (int i = 0; i < 2; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s1.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 3; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s1.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 3; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s1.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5 + 8;
    }
    scenarios.push_back(s1);
    // 关卡2：

    Scenario s2;
    clk = 0;
    for (int boss_count = 1; boss_count <= 4; boss_count++) {
        int id = rand() % enemyPrototypes_boss.size();
        int x = rand() % 400 + 50, y = rand() % 400 + 50;
        s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_boss[id]);
        //接下来是小怪
        for (int i = 0; i < 4; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 4; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 4; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s2.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5 + 8;
    }
    scenarios.push_back(s2);
    Scenario s3;
    clk = 0;
    for (int boss_count = 1; boss_count <= 5; boss_count++) {
        int id = rand() % enemyPrototypes_boss.size();
        int x = rand() % 400 + 50, y = rand() % 400 + 50;
        s3.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_boss[id]);
        //接下来是小怪
        for (int i = 0; i < 4; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s3.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 5; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s3.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5;
        for (int i = 0; i < 5; i++) {
            id = rand() % enemyPrototypes_small.size();
            x = rand() % 500, y = rand() % 500;
            s3.add(clk, {(qreal)x, (qreal)y}, *enemyPrototypes_small[id]);
        }
        clk += rand() % 5 + 8;
    }
    scenarios.push_back(s3);
}

qreal Scenario::get_hp_rate() const {
    for (int i = 0; i < bosses.size(); i++)
        if (bosses[i]->getHp() > 0) {
            // qDebug() <<"boss_id:" << i <<
            // "now_boss_hp:"<<bosses[i]->getHp()<<endl;
            return (qreal)bosses[i]->getHp() / boss_hpes[i];
        }
    return 0;
}

void Scenario::print_boss() const {
    qDebug() << "print_boss" << endl;
    for (int i = 0; i < enemySpawnConfig.size(); i++) {
        const auto &p = enemySpawnConfig[i];
        if (p.second.is_boss == 1) qDebug() << i << "is boss" << endl;
    }
}

qreal Scenario::get_last_time() const { return countdown; }

void Scenario::advance() {
    if (boss_id == -1 && bosses.size()) {
        boss_id = 0;
        if (boss_id + 1 < boss_time.size()) {
            countdown = (boss_time[boss_id + 1] - boss_time[boss_id]) * 200;
            qDebug() << "一开始:" << countdown << endl;
        } else
            countdown = 2500 ;
    } else if (bosses.size() && boss_id < bosses.size() &&
               bosses[boss_id]->getHp() <= 0) {
        if (boss_id + 1 < boss_time.size())
            countdown += (boss_time[boss_id + 1] - boss_time[boss_id]) * 200;
        else
            countdown = 2500 ;
        boss_id++;
    }
    countdown--;
    // qDebug() << "countdown:" << countdown <<endl;
}

int Scenario::remain_boss_count() const {
    int res = boss_number;
    for (int i = 0; i < bosses.size(); i++)
        if (bosses[i]->getHp() <= 0) res--;
    return res;
}

bool Scenario::is_lose() const {
    // qDebug() << "boss_count:" <<bosses.size() <<"/"<<boss_number<< endl;
    if (countdown < 0) return 1;
    return 0;
}

bool Scenario::is_win() const {
    qDebug() << "boss_count:" << bosses.size() << ":" << boss_id << "/"
             << boss_number << endl;
    if (bosses.size() != boss_number) return 0;
    for (int i = 0; i < bosses.size(); i++)
        if (bosses[i]->getHp() > 0) return 0;
    qDebug() << "scenario_is_win" << endl;
    return 1;
}

int Scenario::is_end() const {
    // qDebug() << "boss_count:" <<bosses.size() <<"/"<<boss_number<< endl;
    if (is_lose()) return -1;
    if (is_win()) return 1;
    return 0;
}
