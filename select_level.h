#ifndef SELECT_LEVEL_H
#define SELECT_LEVEL_H

#include <QMainWindow>
#include <baseboard.h>
#include <vector>
#include<level_menu.h>
#include<mypushbottom.h>

class Select_level : public Baseboard
{
    Q_OBJECT
public:
    explicit Select_level(QWidget *parent = nullptr);

signals:
    void back_clicked();

protected:
    virtual void paintEvent(QPaintEvent * event);
private:
    std :: vector<Mypushbottom*> list_bottom;
};

#endif // SELECT_LEVEL_H
