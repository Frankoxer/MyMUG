#include "performListBlock.h"

performListBlock::performListBlock(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 450);
}

void performListBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(255, 255, 255,0));
    painter.setPen(pen);

    // 绘制文本
    QFont font("Verdana", 16, QFont::Bold);
    // font.setPointSize(16);
    painter.setPen(Qt::white);
    painter.setFont(font);

    // 绘制第一行文本
    painter.drawText(QRect(0, 10, width(), 30), Qt::AlignCenter, "performList:");

    // 绘制第二行文本
    painter.drawText(QRect(0, 40, width(), 30), Qt::AlignCenter, "Perfect:");
    // font.setPointSize(16);
    painter.setPen(Qt::white);
    painter.setFont(font);

    // 绘制 performList 文本
    QString performListStr0 = QString::number(perfect); // 将分数转换为字符串
    painter.drawText(QRect(0, 15, width(), 35), Qt::AlignRight, performListStr0);

    painter.drawText(QRect(0, 40, width(), 30), Qt::AlignCenter, "Good:");

    QString performListStr1 = QString::number(perfect); // 将分数转换为字符串
    painter.drawText(QRect(0, 15, width(), 35), Qt::AlignRight, performListStr1);

    painter.drawText(QRect(0, 40, width(), 30), Qt::AlignCenter, "Miss:");

    QString performListStr2 = QString::number(perfect); // 将分数转换为字符串
    painter.drawText(QRect(0, 15, width(), 35), Qt::AlignRight, performListStr2);

    QWidget::paintEvent(event);
}
