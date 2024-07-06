#ifndef MYMUG_TRACK_H
#define MYMUG_TRACK_H

#include <QWidget>

class Track : public QWidget {
Q_OBJECT

public:
    explicit Track(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif //MYMUG_TRACK_H
