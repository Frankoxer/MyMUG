//
// Created by Frankoxer on 24-7-11.
//

#include "ScoreEnd.h"

ScoreEnd::ScoreEnd(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 200);
}

void ScoreEnd::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(255, 255, 255,0));
    painter.setPen(pen);

    // 绘制文本
    QFont font("Bahnschrift", 32, QFont::Bold);
    // font.setPointSize(16);
    painter.setPen(Qt::white);
    painter.setFont(font);

    // 绘制 score 文本
    QString scoreStr = QString::number(score); // 将分数转换为字符串
    painter.drawText(QRect(0, 5, width(), 65), Qt::AlignLeft, scoreStr);

    QWidget::paintEvent(event);
}