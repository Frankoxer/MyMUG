#include "../../include/noteBlock.h"
#include <QPainter>
#include <QDateTime>

noteBlock::noteBlock(QWidget *parent, int trackIndex, qint64 timestamp)
        : QWidget(parent), trackIndex(trackIndex), timestamp(timestamp) {
    setFixedSize(120, 20);  // 设置音符的大小
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &noteBlock::movenoteBlock);
    timer->start(16);  // 每16毫秒移动一次音符（约60帧每秒）
}

void noteBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制音符
    painter.setBrush(Qt::blue);
    painter.drawRect(0, 0, width(), height());

    QWidget::paintEvent(event);
}

void noteBlock::movenoteBlock() {
    move(x(), y() + 1);  // 每次移动音符1像素
    if (y() > parentWidget()->height()) {
        timer->stop();
        this->deleteLater();  // 如果音符移出屏幕，则删除音符
    }
}
