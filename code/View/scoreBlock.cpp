#include "ScoreBlock.h"

ScoreBlock::ScoreBlock(QWidget *parent) : QWidget(parent) {
    setFixedSize(100, 100); // 设置判定线的大小
}

void ScoreBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(255, 255, 255,0));
    painter.setPen(pen);

    // 绘制文本
    QFont font = painter.font();
    painter.setPen(Qt::white);
    font.setPointSize(16);
    painter.setFont(font);

    // 绘制 "Score:" 文本
    painter.drawText(QRect(0, 10, width(), 30), Qt::AlignCenter, "Score:");

    // 绘制数字 "1" 文本

    QString scoreStr = QString::number(score); // 将分数转换为字符串
    painter.drawText(QRect(0, 50, width(), 30), Qt::AlignCenter, scoreStr);

    QWidget::paintEvent(event);
}
