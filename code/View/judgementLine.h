#ifndef JUDGEMENTLINE_H
#define JUDGEMENTLINE_H

#include <QWidget>
#include <QPainter>

class JudgementLine : public QWidget {
Q_OBJECT

public:
    explicit JudgementLine(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // JUDGEMENTLINE_H
