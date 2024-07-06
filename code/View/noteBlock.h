#ifndef noteBlock_H
#define noteBlock_H

#include <QWidget>
#include <QTimer>

class noteBlock : public QWidget {
Q_OBJECT

public:
    explicit noteBlock(QWidget *parent = nullptr, int trackIndex = 0, qint64 timestamp = 0);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;
    int trackIndex;
    qint64 timestamp;  // 音符应该被击打的时间戳

private slots:
    void movenoteBlock();
};

#endif // noteBlock_H
