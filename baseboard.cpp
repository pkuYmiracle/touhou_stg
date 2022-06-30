#include "baseboard.h"

#include <QPainter>
#include <QPixmap>

#include "ui_baseboard.h"

Baseboard::Baseboard(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Baseboard) {
    ui->setupUi(this);
    this->setWindowTitle("STG");

    this->setWindowIcon(QIcon(":/backboard/icon.png"));
    this->setFixedSize(800, 1000);
}

Baseboard::~Baseboard() { delete ui; }

void Baseboard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap(":/backboard/2.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}
