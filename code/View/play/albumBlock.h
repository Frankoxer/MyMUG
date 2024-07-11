#ifndef ALBUMBLOCK_H
#define ALBUMBLOCK_H

#include <QWidget>
#include <QString>
#include <QPixmap>

class albumBlock : public QWidget {
Q_OBJECT
public:
    explicit albumBlock(QWidget *parent = nullptr);
    void setalbumPath(const QString &albumPath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_albumPath;
    QPixmap m_albumBlockPixmap;
};

#endif // Block_H