#include "startboard.h"
#include "baseboard.h"
#include"mypushbutton.h"
#include<QTimer>
Startboard::Startboard(QWidget *parent)
    : Baseboard {parent}
{
    this -> setWindowTitle("getting start...");
    Mypushbutton *start_button = new Mypushbutton(this,true,
                                                  ":/backboard/start.png",150);
    start_button->resize(200,200);
    start_button->move((this->width() - start_button->width())/2,this->height()
                                                                 *3/4 - start_button->height()/2);
    connect(start_button,&Mypushbutton :: clicked,[&](){
        QTimer::singleShot(300,[&](){
            this -> hide();
            this->level_scene .show();
        });
    });
    connect(&this->level_scene,&Select_level::back_clicked,[&](){
        QTimer::singleShot(300,[&](){
            this -> show();
            this->level_scene .hide();
        });
    });
}
