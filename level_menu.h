#ifndef LEVEL_MENU_H
#define LEVEL_MENU_H

#include <baseboard.h>
#include <vector>
#include <QString>
#include "mypushbutton.h"
class Level_menu : public Baseboard
{
    Q_OBJECT
private:
    int id,pos;
    std::vector<QString>    characters,
                            nxt_board_urls;
    std::vector<int>        bulletGroupId;
    Mypushbutton            *character_postion;
public:
    explicit Level_menu(QWidget *parent = nullptr,int _id = 0);

signals:
    void back_clicked();

protected:
    virtual void paintEvent(QPaintEvent * event);
private:
    void turn_left();
    void turn_right();

};

#endif // LEVEL_MENU_H
