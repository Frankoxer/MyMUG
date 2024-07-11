#include "albumBlock.h"
#include <QPainter>
#include <QFont>
#include <QPen>
#include <QDebug>
#include <iostream>

albumBlock::albumBlock(QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(400, 400); // 设置 albumBlock 的大小
}

void albumBlock::setalbumPath(const QString &albumPath) {
    // std::cout << "setting album path" << std::endl;
    m_albumPath = albumPath;
}


void albumBlock::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!m_albumBlockPixmap.load(m_albumPath)) {
        qDebug() << "Failed to load albumBlock image.";
    } else {
        // 缩放图片至400x400大小
        QPixmap scaledPixmap = m_albumBlockPixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // 绘制缩放后的图片
        painter.drawPixmap(0, 0, scaledPixmap);
    }

    QWidget::paintEvent(event);
}