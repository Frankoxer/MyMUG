#include "levelBlock.h"

levelBlock::levelBlock(QWidget *parent) : QWidget(parent) {
    setFixedSize(50, 50); // 设置 levelBlock 的大小
}

void levelBlock::setLevel(const QString &level_char) {
    this->level = level_char;
    update(); // 重新绘制以显示新标题
}

void levelBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    QPen pen(QColor(255, 255, 255, 0)); // 白色边框
    painter.setPen(pen);

    // 绘制矩形
    painter.drawRect(0, 0, width(), height());

    // 绘制文本
    QFont font("Verdana", 16);
    painter.setPen(Qt::white);
    painter.setFont(font);

    // 绘制乐谱名称
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignRight, level);

    QWidget::paintEvent(event);
}
