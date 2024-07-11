//
// Created by Frankoxer on 24-7-11.
//

#ifndef SCOREEND_H
#define SCOREEND_H

#include <QWidget>
#include <QPainter>

class ScoreEnd : public QWidget {
    Q_OBJECT

    public:
    explicit ScoreEnd(QWidget *parent = nullptr);
    void setScore(int score) { this->score = score; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int score = 0;
};

#endif //SCOREEND_H
