#ifndef ACCURACYBLOCK_H
#define ACCURACYBLOCK_H

#include <QWidget>
#include <QPainter>

class accuracyBlock : public QWidget {
Q_OBJECT

public:
    explicit accuracyBlock(QWidget *parent = nullptr);
    void setaccuracy(int accuracy) { this->accuracy = accuracy; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int accuracy = 0;
};

#endif // accuracyBlock_H
