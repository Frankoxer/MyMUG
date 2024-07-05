#include "../include/track.h"
#include <QPainter>

Track::Track(QWidget *parent) : QWidget(parent) {
    setFixedSize(120, 900);  // 设置音轨的大小
}

void Track::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制音轨背景
    painter.setBrush(Qt::gray);
    painter.drawRect(0, 0, width(), height());

    QWidget::paintEvent(event);
}
