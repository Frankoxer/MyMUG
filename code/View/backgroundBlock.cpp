#include "backgroundBlock.h"
#include <QPainter>
#include <QFont>
#include <QPen>
#include <QDebug>

backgroundBlock::backgroundBlock(QWidget *parent)
        : QWidget(parent)
{
    setFixedSize(1440, 900); // 设置 backgroundBlock 的大小

    // 加载背景图片
    if (!m_backgroundBlockPixmap.load("../resources/covers/Chronostasis.png")) { // 注意这里使用资源系统路径
        qDebug() << "Failed to load backgroundBlock image.";
    }
}

//void backgroundBlock::setTitle(const QString &title)
//{
//    m_title = title;
//    update(); // 重新绘制以显示新标题
//}

void backgroundBlock::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制背景图片
    if (!m_backgroundBlockPixmap.isNull()) {
        painter.drawPixmap(0, 0, m_backgroundBlockPixmap);
    }


    QWidget::paintEvent(event);
}