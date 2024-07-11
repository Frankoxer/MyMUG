#ifndef noteBlock_H
#define noteBlock_H

#include <QWidget>
#include <QTimer>

class noteBlock : public QWidget {
Q_OBJECT

public:
    explicit noteBlock(QWidget *parent = nullptr, int trackIndex = 0, int startY=0);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int trackIndex;
    int startY;

};

#endif // noteBlock_H
