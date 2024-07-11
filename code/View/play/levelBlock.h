#ifndef LEVELBLOCK_H
#define LEVELBLOCK_H

#include <QWidget>
#include <QPainter>

class levelBlock : public QWidget {
Q_OBJECT

public:
    explicit levelBlock(QWidget *parent = nullptr);
    void setLevel(const QString &level_char);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString level;
};

#endif // levelBLOCK_H
