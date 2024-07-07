#ifndef BACKGROUNDBLOCK_H
#define BACKGROUNDBLOCK_H

#include <QWidget>
#include <QString>
#include <QPixmap>

class backgroundBlock : public QWidget {
Q_OBJECT
public:
    explicit backgroundBlock(QWidget *parent = nullptr);
    void setTitle(const QString &title);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_title;
    QPixmap m_backgroundBlockPixmap;
};

#endif // backgroundBlock_H