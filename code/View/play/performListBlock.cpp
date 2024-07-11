#include "performListBlock.h"

performListBlock::performListBlock(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 450);
}

void performListBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(255, 255, 255, 0));
    painter.setPen(pen);

    QFont font("Bahnschrift", 16, QFont::Bold);
    painter.setPen(Qt::white);
    painter.setFont(font);


    // 绘制"Perfect:"文本，金色
    painter.setPen(QColor(255, 215, 0));
    painter.drawText(QRect(0, 50, width(), 30), Qt::AlignLeft, "Perfect:  " + QString::number(perfect));

    // 绘制"Good:"文本，浅蓝色
    painter.setPen(QColor(0, 191, 255));
    painter.drawText(QRect(0, 110, width(), 30), Qt::AlignLeft, "Good:  " + QString::number(good));

    // 绘制"Miss:"文本，白色
    painter.setPen(Qt::white);
    painter.drawText(QRect(0, 170, width(), 30), Qt::AlignLeft, "Miss:  " + QString::number(miss));

    QWidget::paintEvent(event);
}
