#ifndef PERFORMLISTBLOCK_H
#define PERFORMLISTBLOCK_H

#include <QWidget>
#include <QPainter>

class performListBlock : public QWidget {
Q_OBJECT

public:
    explicit performListBlock(QWidget *parent = nullptr);
    void setperformList(int perfect, int good, int miss) { this->perfect = perfect; this->good = good; this->miss = miss; }



protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int perfect = 0;
    int good = 0;
    int miss = 0;
};

#endif // performListBlock_H
