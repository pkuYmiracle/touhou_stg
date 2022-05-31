#include "mypushbottom.h"
#include<QPushButton>
#include<QPainter>
#include<QPropertyAnimation>
#include<QPixmap>
#include<QTimer>
Mypushbottom::Mypushbottom(QWidget *parent,bool up_down ,QString _load_path,int updowntime)
    : QPushButton{parent},is_up_down(up_down),load_path(_load_path),up_down_time(updowntime)
{
    if(up_down)
        connect (this,&Mypushbottom::clicked,this,&Mypushbottom::when_clicked);
}

void Mypushbottom::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   QPixmap pixmap;
   pixmap.load(load_path);
   painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

}

void Mypushbottom::move_down()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry",this);
    animation ->setStartValue(this->geometry());
    animation ->setEndValue(QRect(this->x(),this->y() + 10,this->width(),this->height()));
    animation ->setDuration( 100);
    animation ->start(QAbstractAnimation::DeleteWhenStopped);
}

void Mypushbottom::move_up()
{

    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry",this);
    animation ->setStartValue(this->geometry());
    animation ->setEndValue(QRect(this->x(),this->y() - 10,this->width(),this->height()));
    animation ->setDuration( up_down_time);
    animation ->start(QAbstractAnimation::DeleteWhenStopped);
}

void Mypushbottom::when_clicked()
{
   setEnabled(false);
   move_down();
   QTimer::singleShot(up_down_time,[&](){
       move_up();
   });
   QTimer::singleShot(up_down_time * 2,[&](){
       setEnabled(true);
   });
}
