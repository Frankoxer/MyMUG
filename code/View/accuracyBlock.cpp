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
    QFont font("Accuracy", 16, QFont::Bold);
    // font.setPointSize(16);
    painter.setPen(Qt::white);
    painter.setFont(font);

    //绘制 "accuracy:" 文本
    painter.drawText(QRect(0, 10, width(), 30), Qt::AlignCenter, "accuracy:");

    // 绘制 accuracy 文本
    QString accuracyStr = QString::number(accuracy); // 将分数转换为字符串
    painter.drawText(QRect(0, 15, width(), 35), Qt::AlignRight, accuracyStr);

    QWidget::paintEvent(event);
}
