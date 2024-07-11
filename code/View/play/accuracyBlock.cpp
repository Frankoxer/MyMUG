#include "accuracyBlock.h"

accuracyBlock::accuracyBlock(QWidget *parent) : QWidget(parent) {
    setFixedSize(200, 150);
}

void accuracyBlock::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(QColor(255, 255, 255,0));
    painter.setPen(pen);

    // 绘制文本
    QFont font("Bahnschrift", 16, QFont::Bold);
    // font.setPointSize(16);
    painter.setPen(Qt::white);
    painter.setFont(font);

    // 绘制 accuracy 文本，将十进制 0~1 浮点数转化为两位小数的百分数
    QString accuracyStr = QString::number(accuracy * 100, 'f', 2) + "%";
    painter.drawText(QRect(0, 10, width(), 40), Qt::AlignCenter, "Accuracy:  " + accuracyStr);

    QWidget::paintEvent(event);
}
