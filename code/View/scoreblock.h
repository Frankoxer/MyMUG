#ifndef SCOREBLOCK_H
#define SCOREBLOCK_H

#include <QWidget>
#include <QPainter>

class ScoreBlock : public QWidget {
Q_OBJECT

public:
    explicit ScoreBlock(QWidget *parent = nullptr);
    void setScore(int score) { this->score = score; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int score = 0;
};

#endif // ScoreBlock_H
