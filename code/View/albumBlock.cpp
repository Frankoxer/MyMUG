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

    if (!m_albumBlockPixmap.load(m_albumPath)) { // 注意这里使用资源系统路径
        qDebug() << "Failed to load albumBlock image.";
    }

    // 绘制背景图片
    if (!m_albumBlockPixmap.isNull()) {
        painter.drawPixmap(0, 0, m_albumBlockPixmap);
    }

    // m_painted = true;
    QWidget::paintEvent(event);
}