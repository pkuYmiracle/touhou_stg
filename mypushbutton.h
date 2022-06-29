#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include<QPushButton>
#include<QString>
class Mypushbutton : public QPushButton
{
    Q_OBJECT
private:
    QString load_path;
    bool is_up_down;
    int up_down_time;
public:
    explicit Mypushbutton(QWidget *parent = nullptr,bool up_down = 1,QString _load_path = "",int up_down_time = 100);
private:
    virtual void paintEvent(QPaintEvent * event);
    void move_down();
    void move_up();

public slots:
    void when_clicked();
signals:

};

#endif // MYPUSHBUTTON_H
