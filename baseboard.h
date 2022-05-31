#ifndef BASEBOARD_H
#define BASEBOARD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Baseboard; }
QT_END_NAMESPACE

class Baseboard : public QMainWindow
{
    Q_OBJECT

public:
    Baseboard(QWidget *parent = nullptr);
    ~Baseboard();
protected:
    virtual void paintEvent(QPaintEvent * event);
private:
    Ui::Baseboard *ui;
};
#endif // BASEBOARD_H
