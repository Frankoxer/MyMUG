#include "mainwindow.h"
#include "ui_MainWindow.h"
// #include "D:\eclipse_workspace\cpp_in_CLION\MyMUG\cmake-build-debug\MyMUG_autogen\include\ui_MainWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDateTime>
#include <iostream>

// typedef struct {
//     int x;
//     int y;
// } NoteInfo;

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 设置固定窗口大小
    setFixedSize(1440, 900);

    // 创建 QLabel 并设置背景图片
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, 1440, 900);  // 设置 QLabel 大小与窗口一致
//    QPixmap backgroundPixmap(":/background.png"); // 使用资源路径加载图片
    QPixmap backgroundPixmap("../resources/covers/Chronostasis.png"); // 使用资源路径加载图片
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);  // 使图片缩放填满整个 QLabel
    backgroundLabel->lower();  // 将 QLabel 放置在底层

    // 创建音轨和音符
    createTracks();
    // createNotes();
    // noteBlocks.clear();
    // int startY = 800;
    // std::cout << "First iter" << std::endl;
    // for(int i = 0;i < 4; ++i) {
    //     noteBlock *note = new noteBlock(tracks[i], i, startY);
    //     note->move(0, startY);
    //     noteBlocks.append(note);
    //
    // }
}

MainWindow::~MainWindow() {
    delete ui;

    // 清理 activeKeys 中的 KeyEvent 对象
    qDeleteAll(activeKeys);
    activeKeys.clear();
}

void MainWindow::createTracks() {
    int startX = 480;  // 起始 X 位置
    int gap = 120;     // 轨道间距

    for (int i = 0; i < 4; ++i) {
        Track *track = new Track(this);
        track->move(startX + i * gap, 0);
        tracks.append(track);
    }
}

void MainWindow::recieveActiveNotes(std::vector<NoteInfo> *activeNotesPtr) {
    this->activeNotes = activeNotesPtr;
}

void MainWindow::createNotes() {
    if (activeNotes == nullptr)   // 确保activeNotes指针有效
    {
        int startY = 100;
        std::cout << "First iter" << std::endl;
        for(int i = 0;i < 4; ++i) {
            noteBlock *note = new noteBlock(tracks[i], i, startY);
            note->move(0, startY);
            noteBlocks.append(note);

        }
        std::cout << noteBlocks.size() << std::endl;
    }else {
        qDeleteAll( noteBlocks );
        noteBlocks.clear();
        for ( auto noteInfo : *activeNotes ) {
            int trackIndex = (noteInfo.x / 120) - 4; // 计算轨道索引
            // std::cout << "trackIndex: " << trackIndex << std::endl;
            noteBlock *note = new noteBlock(tracks[trackIndex], trackIndex, noteInfo.y);
            std::cout << noteInfo.y << std::endl;
            note->move(0 ,noteInfo.y);
            noteBlocks.append(note);
            note->show();
        }
        // std::cout << noteBlocks.size() << std::endl;
    }
    // update();
}


void MainWindow::updateView() {
    // 重新创建音符
    createNotes();
    // createTracks();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();

    // 更新 keyFromView[4] 数组
    if (key == Qt::Key_D) keyFromView[0] = true;
    if (key == Qt::Key_F) keyFromView[1] = true;
    if (key == Qt::Key_J) keyFromView[2] = true;
    if (key == Qt::Key_K) keyFromView[3] = true;

    // qDebug() << "Key Pressed: " << event->text() << " (" << key << ")";
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();

    // 更新 key[4] 数组
    if (key == Qt::Key_D) keyFromView[0] = false;
    if (key == Qt::Key_F) keyFromView[1] = false;
    if (key == Qt::Key_J) keyFromView[2] = false;
    if (key == Qt::Key_K) keyFromView[3] = false;

    // qDebug() << "Key Released: " << event->text() << " (" << key << ")";
}

bool* MainWindow::outputKey() {
    return keyFromView;
}

