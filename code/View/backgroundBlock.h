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
    void setBackgroundPath(const QString &backgroundPath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_title;
    QString m_backgroundPath;
    QPixmap m_backgroundBlockPixmap;
    bool m_painted = false;
};

#endif // backgroundBlock_H