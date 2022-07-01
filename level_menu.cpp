#include "level_menu.h"

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "game/bulletgroup.h"
#include "game/gamecontroller.h"
#include "game_board.h"
#include "mypushbutton.h"
Level_menu::Level_menu(QWidget *parent, int _id)
    : Baseboard{parent}, id(_id), pos(0) {
    qDebug() << id << endl;
    this->setWindowTitle("choose one player");

    Mypushbutton *back_button =
        new Mypushbutton(this, true, ":/backboard/back.png", 150);
    back_button->resize(150, 130);
    back_button->move(0, this->height() - back_button->height());
    connect(back_button, &Mypushbutton ::clicked,
            [&]() { QTimer::singleShot(300, [&]() { emit back_clicked(); }); });

    Mypushbutton *chose =
        new Mypushbutton(this, false, ":/backboard/player_select.png", 150);
    chose->resize(400, 100);
    chose->move(this->width() / 4, this->height() / 8);

    Mypushbutton *left_button =
        new Mypushbutton(this, true, ":/backboard/left.png", 150);
    left_button->resize(100, 100);
    left_button->move(0, this->height() / 2);
    connect(left_button, &Mypushbutton ::clicked,
            [&]() { QTimer::singleShot(300, [&]() { this->turn_left(); }); });

    Mypushbutton *right_button =
        new Mypushbutton(this, true, ":/backboard/right.png", 150);
    right_button->resize(100, 100);
    right_button->move(this->width() - right_button->width(),
                       this->height() / 2);
    connect(right_button, &Mypushbutton ::clicked,
            [&]() { QTimer::singleShot(300, [&]() { this->turn_right(); }); });

    characters.push_back(":/people/big1.png");
    characters.push_back(":/people/big2.png");
    characters.push_back(":/people/big3.png");
    characters.push_back(":/people/slpl01a.png");
    nxt_board_urls.push_back(":/game/assets/player01.png");
    nxt_board_urls.push_back(":/game/assets/player.png");
    nxt_board_urls.push_back(":/game/assets/player02.png");
    nxt_board_urls.push_back(":/game/assets/player03.png");
    bulletGroupId = {9, 10, 11, 12};

    character_postion = new Mypushbutton(this, true, characters[pos], 150);
    connect(character_postion, &Mypushbutton ::clicked, [&]() {
        QTimer::singleShot(300, [&]() {
            qDebug() << "game_start" << endl;
            this->hide();
            std::vector<QString> lis;
            lis.push_back("level: " + QString::number(1 + id));
            lis.push_back(QString::number(id));
            lis.push_back(nxt_board_urls[pos]);
            GameController *gc = new GameController(
                lis, this, &player_bulletGroups[pos]);

            this->hide();
        });
    });
    character_postion->resize(400, 500);
    character_postion->move(
        100 + 100, this->height() / 2 - character_postion->height() / 2);
}

void Level_menu::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/backboard/3.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}
void Level_menu::turn_left() {
    pos = (pos + characters.size() - 1) % characters.size();
    delete character_postion;

    character_postion = new Mypushbutton(this, true, characters[pos], 150);
    connect(character_postion, &Mypushbutton ::clicked, [&]() {
        QTimer::singleShot(300, [&]() {
            qDebug() << "game_start" << endl;
            this->hide();
            std::vector<QString> lis;
            lis.push_back("level: " + QString::number(1 + id));
            lis.push_back(QString::number(id));
            lis.push_back(nxt_board_urls[pos]);
            GameController *gc = new GameController(
                lis, this, &player_bulletGroups[pos]);

            this->hide();
        });
    });
    character_postion->resize(400, 500);
    character_postion->move(
        100 + 100, this->height() / 2 - character_postion->height() / 2);

    character_postion->show();
}
void Level_menu::turn_right() {
    pos = (pos + characters.size() + 1) % characters.size();
    delete character_postion;
    character_postion = new Mypushbutton(this, true, characters[pos], 150);
    connect(character_postion, &Mypushbutton ::clicked, [&]() {
        QTimer::singleShot(300, [&]() {
            qDebug() << "game_start" << endl;
            this->hide();
            std::vector<QString> lis;
            lis.push_back("level: " + QString::number(1 + id));
            lis.push_back(QString::number(id));
            lis.push_back(nxt_board_urls[pos]);
            GameController *gc = new GameController(
                lis, this, &player_bulletGroups[pos]);

            this->hide();
        });
    });
    character_postion->resize(400, 500);
    character_postion->move(
        100 + 100, this->height() / 2 - character_postion->height() / 2);

    character_postion->show();
}
