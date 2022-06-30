#include "select_level.h"

#include <mypushbutton.h>

#include <QPainter>
#include <QPixmap>
#include <QTimer>

#include "baseboard.h"
#include "level_menu.h"
Select_level::Select_level(QWidget *parent) : Baseboard{parent} {
    this->setWindowTitle("choose one level");

    Mypushbutton *back_button =
        new Mypushbutton(this, true, ":/backboard/back.png", 150);
    back_button->resize(150, 130);
    back_button->move(0, this->height() - back_button->height());
    connect(back_button, &Mypushbutton ::clicked,
            [&]() { emit back_clicked(); });

    Mypushbutton *title =
        new Mypushbutton(this, false, ":/backboard/level_select.png", 150);
    title->resize(600, 100);
    title->move(100, 150);

    std::vector<QString> level;
    level.push_back(":/game/assets/easy.png");
    level.push_back(":/game/assets/normal.png");
    level.push_back(":/game/assets/hard.png");
    level.push_back(":/game/assets/lunatic.png");
    for (int i = 0; i < 4; i++) {
        this->list_bottom.push_back(
            new Mypushbutton(this, true, level[i], 150));
        this->list_bottom[i]->resize(600, 100);
        this->list_bottom[i]->move(100, i * 130 + 300);
        connect(this->list_bottom[i], &Mypushbutton ::clicked, [=]() {
            QTimer::singleShot(300, [&]() {
                Level_menu *level_menu = new Level_menu(this, i);
                level_menu->show();
                this->hide();
                connect(level_menu, &Level_menu ::back_clicked, [=] {
                    this->show();
                    level_menu->hide();
                });
            });
        });
    }
}

void Select_level::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/backboard/1.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}
