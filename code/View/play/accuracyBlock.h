#ifndef ACCURACYBLOCK_H
#define ACCURACYBLOCK_H

#include <QWidget>
#include <QPainter>

class accuracyBlock : public QWidget {
Q_OBJECT

public:
    explicit accuracyBlock(QWidget *parent = nullptr);
    void setaccuracy(double accuracy) { this->accuracy = accuracy; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double accuracy = 0.0;
};

#endif // accuracyBlock_H
