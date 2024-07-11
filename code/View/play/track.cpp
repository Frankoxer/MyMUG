#include "track.h"
#include <QPainter>

Track::Track(QWidget *parent) : QWidget(parent) {
    setFixedSize(120, 920);  // 设置音轨的大小
}

void Track::paintEvent(QPaintEvent *event) {
    // if(ispaint) {
    //     return;
    // }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制音轨背景
//    painter.setBrush(Qt::gray);
    painter.setBrush(QColor(12,12,12,170));

    QPen pen(QColor(255, 255, 255,100));
    painter.setPen(pen);



    painter.drawRect(0, 0, width(), height());
//    painter.drawRoundedRect(0, 0, width(), height(), 10, 10);

    QWidget::paintEvent(event);

    // ispaint = true;
}
