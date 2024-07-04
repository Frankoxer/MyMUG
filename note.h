#ifndef NOTE_H
#define NOTE_H

#include <QWidget>
#include <QTimer>

class Note : public QWidget {
Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr, int trackIndex = 0, qint64 timestamp = 0);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timer;
    int trackIndex;
    qint64 timestamp;  // 音符应该被击打的时间戳

private slots:
    void moveNote();
};

#endif // NOTE_H
