#include "ComboBlock.h"

ComboBlock::ComboBlock(QWidget *parent) : QWidget(parent) {
    setFixedSize(100, 100); // 设置判定线的大小
}

void ComboBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制判定线背景
//    painter.setBrush(Qt::darkBlue);
    painter.setBrush(QColor(205,149,12,1));


    QPen pen(QColor(255, 255, 255,10));
    painter.setPen(pen);


//    painter.drawRect(0, 0, width(), height());
    painter.drawRoundedRect(0, 0, width(), height(), 20, 20);

    // 绘制文本
    QFont font = painter.font();
    font.setPointSize(16);
    painter.setFont(font);

    // 绘制 "Combo:" 文本
    painter.drawText(QRect(0, 10, width(), 30), Qt::AlignCenter, "Combo:");

    // 绘制数字 "1" 文本
    painter.drawText(QRect(0, 50, width(), 30), Qt::AlignCenter, "1");

    QWidget::paintEvent(event);
}
