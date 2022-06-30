#ifndef SELECT_LEVEL_H
#define SELECT_LEVEL_H

#include <baseboard.h>
#include <level_menu.h>
#include <mypushbutton.h>

#include <QMainWindow>
#include <vector>

class Select_level : public Baseboard {
    Q_OBJECT
public:
    explicit Select_level(QWidget *parent = nullptr);

signals:
    void back_clicked();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    std ::vector<Mypushbutton *> list_bottom;
};

#endif  // SELECT_LEVEL_H
