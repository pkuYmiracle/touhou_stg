#include "level_menu.h"
#include "mypushbottom.h"
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include "game_board.h"
Level_menu::Level_menu(QWidget *parent,int _id)
    : Baseboard{parent},id(_id),pos(0)
{

    this -> setWindowTitle("choose one level");

    Mypushbottom *back_button = new Mypushbottom(this,true,
                                                  ":/backboard/back.png",150);
    back_button->resize(100,100);
    back_button->move(0,this->height()- back_button->height());
    connect(back_button,&Mypushbottom :: clicked,[&](){
        emit back_clicked();
    });


    Mypushbottom *left_button = new Mypushbottom(this,true,
                                                  ":/backboard/back.png",150);
    left_button->resize(100,100);
    left_button->move(0,this->height()/2);
    connect(left_button,&Mypushbottom :: clicked,[&](){
        QTimer::singleShot(300,[&](){
            this -> turn_left();
        });
    });


    Mypushbottom *right_button = new Mypushbottom(this,true,
                                                  ":/backboard/back.png",150);
    right_button->resize(100,100);
    right_button->move(this->width()-right_button->width(),this->height()/2);
    connect(right_button,&Mypushbottom :: clicked,[&](){
        QTimer::singleShot(300,[&](){
            this -> turn_right();
        });
    });

    characters.push_back(":/people/orange.png");
    characters.push_back(":/people/qi.png");
    characters.push_back(":/people/wu.png");

    character_postion = new Mypushbottom(this,true,characters[pos],150);
    connect(character_postion,&Mypushbottom :: clicked,[&](){
        QTimer::singleShot(300,[&](){
             Game_board * game = new Game_board(this,id,characters[pos]);
             game ->show();
             this->hide();
        });
    });
    character_postion->resize(500,600);
    character_postion->move(100 + 50 ,this->height()/2 - character_postion->height()/2);

}

void Level_menu::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPixmap pixmap(":/backboard/3.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
void Level_menu::turn_left()
{

    pos = (pos + characters.size() - 1) %  characters.size();
    delete character_postion;

    character_postion = new Mypushbottom(this,true,
                                                  characters[pos],150);
    connect(character_postion,&Mypushbottom :: clicked,[&](){
        QTimer::singleShot(300,[&](){
             Game_board * game = new Game_board(this,id,characters[pos]);
             game ->show();
             this->hide();
        });
    });
    character_postion->resize(500,600);
    character_postion->move(100 + 50 ,this->height()/2 - character_postion->height()/2);
    character_postion->show();
}
void Level_menu::turn_right()
{

    pos = (pos + characters.size() + 1) %  characters.size();
    delete character_postion;
    character_postion = new Mypushbottom(this,true,
                                                  characters[pos],150);
    connect(character_postion,&Mypushbottom :: clicked,[&](){
        QTimer::singleShot(300,[&](){
             Game_board * game = new Game_board(this,id,characters[pos]);
             game ->show();
             this->hide();
        });
    });
    character_postion->resize(500,600);
    character_postion->move(100 + 50 ,this->height()/2 - character_postion->height()/2);
    character_postion->show();

}
