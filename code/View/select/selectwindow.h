//
// Created by Frankoxer on 24-7-11.
//

#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <vector>

#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QLabel>

class SelectWindow : public QWidget {
Q_OBJECT

public:
    explicit SelectWindow(QWidget *parent = nullptr);
    void setList(const std::vector <QString> &song);
    void onBtnStartClicked();
    ~SelectWindow() override;

signals:
    void startGame(QString song);

private:
    QListWidget songList;
    QPushButton btnStart;
    std::vector <QString> *List;
    QPixmap background;
    QLabel title;
    QLabel intro;
};


#endif //SELECTWINDOW_H
