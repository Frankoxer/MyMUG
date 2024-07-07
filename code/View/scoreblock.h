#ifndef SCOREBLOCK_H
#define SCOREBLOCK_H

#include <QWidget>
#include <QPainter>

class ScoreBlock : public QWidget {
Q_OBJECT

public:
    explicit ScoreBlock(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // ScoreBlock_H
