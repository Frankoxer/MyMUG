#include "backgroundBlock.h"
#include <QPainter>
#include <QFont>
#include <QPen>
#include <QDebug>
#include <iostream>

backgroundBlock::backgroundBlock(QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(1440, 900); // 设置 backgroundBlock 的大小

    // // 加载背景图片
    // if (!m_backgroundBlockPixmap.load("../resources/covers/Chronostasis.png")) { // 注意这里使用资源系统路径
    //     qDebug() << "Failed to load backgroundBlock image.";
    // }
}

void backgroundBlock::setBackgroundPath(const QString &backgroundPath) {
    std::cout << "setting background path" << std::endl;
    m_backgroundPath = backgroundPath;
}


void backgroundBlock::paintEvent(QPaintEvent *event)
{
    // if(m_painted) {
    //     return;
    // }
    // std::cout << "painting background" << std::endl;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!m_backgroundBlockPixmap.load(m_backgroundPath)) { // 注意这里使用资源系统路径
        qDebug() << "Failed to load backgroundBlock image.";
    }

    // 绘制背景图片
    if (!m_backgroundBlockPixmap.isNull()) {
        painter.drawPixmap(0, 0, m_backgroundBlockPixmap);
    }

    // m_painted = true;
    QWidget::paintEvent(event);
}