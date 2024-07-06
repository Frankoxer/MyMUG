#include "noteBlock.h"
#include <QPainter>

noteBlock::noteBlock(QWidget *parent, int trackIndex, int startY)
        : QWidget(parent), trackIndex(trackIndex), startY(startY) {
    setFixedSize(120, 20);  // 设置音符的大小
    move( (trackIndex+4) * 120, startY); // 根据轨道索引和起始y位置设置初始位置
}

void noteBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制音符
    painter.setBrush(Qt::blue);
    painter.drawRect(0, 0, width(), height());

    QWidget::paintEvent(event);
}
