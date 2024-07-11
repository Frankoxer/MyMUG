#include "JudgementLine.h"

JudgementLine::JudgementLine(QWidget *parent) : QWidget(parent) {
    setFixedSize(480, 6); // 设置判定线的大小
}

void JudgementLine::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制判定线背景
//    painter.setBrush(Qt::darkBlue);
    painter.setBrush(QColor(205,149,12,220));

    QPen pen(QColor(255, 255, 255,10));
    painter.setPen(pen);


    painter.drawRect(0, 0, width(), height());
//    painter.drawRoundedRect(0, 0, width(), height(), 10, 10);


    QWidget::paintEvent(event);
}
