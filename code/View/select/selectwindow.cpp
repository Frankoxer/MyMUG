//
// Created by Frankoxer on 24-7-11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SelectWindow.h" resolved

#include "selectwindow.h"
#include <QListWidgetItem>
#include <QDebug>

SelectWindow::SelectWindow(QWidget *parent) :
    QWidget(parent), songList(this), btnStart("Start", this), title(this), intro(this){
    setFixedSize(1200, 700);
    // 先插个背景图片铺满，使用路径../resources/covers/Chronostasis.png
    background.load("../resources/images/welcome.png");
    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background.scaled(size(), Qt::IgnoreAspectRatio)));
    setPalette(palette);

    // 标题叫 MyMUG，放在左边，字体设置为Bahnschrift，大小为32
    title.setText("MyMUG");
    title.setGeometry(300, 175, 250, 100);
    title.setStyleSheet("font-family:Comic Sans MS;font-size:60px;color:white");

    // 副标题：Our DIY Rhthm Game!!，放在左边，字体设置为Comic Sans MS，大小为16
    intro.setText("Our DIY Rhythm Game!!");
    intro.setGeometry(250, 290, 350, 100);
    intro.setStyleSheet("font-family:Comic Sans MS;font-size:30px;color:white");


    // 将songList的属性和布局设置为界面右侧
    // 假设我们想要songList的宽度为400，那么X坐标为800（1200-400）
    songList.setGeometry(850, 150, 200, 300);

    // 按钮字体为Comic Sans MS，大小为16
    btnStart.setStyleSheet("font-family:Comic Sans MS;font-size:16px");
    // 将btnStart的属性和布局设置为紧接在songList下方
    btnStart.setGeometry(900, 500, 100, 50);
    connect(&btnStart, &QPushButton::clicked, this, &SelectWindow::onBtnStartClicked);
}

void SelectWindow::setList(const std::vector<QString> &songs) {
    for (const auto &song : songs) {
        QListWidgetItem *item = new QListWidgetItem(song);
        songList.addItem(item);
    }
}

void SelectWindow::onBtnStartClicked() {
    if (songList.currentItem()) {
        // std::cout << songList.currentItem()->text().toStdString() << std::endl;
        emit startGame(songList.currentItem()->text());
        close();
    }
}

SelectWindow::~SelectWindow() {
    delete List;
    delete &songList;
    delete &btnStart;
}