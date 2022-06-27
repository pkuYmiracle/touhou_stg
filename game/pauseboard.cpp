#include "pauseboard.h"
#include "mypushbottom.h"

Pauseboard::Pauseboard(QWidget *parent)
    : QMainWindow {parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    Mypushbottom *start_button = new Mypushbottom(parent, true,
                                                  ":/game/assets/button.png",150);
    start_button->show();
    setWindowOpacity(0);
    this -> setFixedSize(700,700);
    start_button->resize(500,100);
    start_button->move((this->width() - start_button->width())/2,
                        this->height()*3/4 - start_button->height()/2);
//    connect(start_button,&Mypushbottom :: clicked,[&](){
//        QTimer::singleShot(300,[&](){
//            this -> hide();
//            this->level_scene .show();
//        });
//    });
//    connect(&this->level_scene,&Select_level::back_clicked,[&](){
//        QTimer::singleShot(300,[&](){
//            this -> show();
//            this->level_scene .hide();
//        });
//    });
}
