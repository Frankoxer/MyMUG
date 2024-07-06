#include "mainwindow.h"
//#include "ui_MainWindow.h"
#include "D:\eclipse_workspace\cpp_in_CLION\MyMUG\cmake-build-debug\MyMUG_autogen\include\ui_MainWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 设置固定窗口大小
    setFixedSize(1440, 900);

    // 创建 QLabel 并设置背景图片
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, 1440, 900);  // 设置 QLabel 大小与窗口一致
//    QPixmap backgroundPixmap(":/background.png"); // 使用资源路径加载图片
    QPixmap backgroundPixmap("D:/eclipse_workspace/Qt/MyMUG/background.jpg"); // 使用资源路径加载图片
    backgroundLabel->setPixmap(backgroundPixmap);
    backgroundLabel->setScaledContents(true);  // 使图片缩放填满整个 QLabel
    backgroundLabel->lower();  // 将 QLabel 放置在底层

    // 创建音轨和音符
    createTracks();
    createNotes();
}

MainWindow::~MainWindow() {
    delete ui;

    // 清理 activeKeys 中的 KeyEvent 对象
    qDeleteAll(activeKeys);
    activeKeys.clear();
}

void MainWindow::createTracks() {
    int startX = 440;  // 起始 X 位置
    int gap = 140;     // 轨道间距

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
    if (!activeNotes) return;  // 确保activeNotes指针有效

    for (const auto &noteInfo : *activeNotes) {
        noteBlock *note = new noteBlock(tracks[(noteInfo.x / 120) - 4], (noteInfo.x / 120) - 4, noteInfo.y);
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();

    // 更新 key[4] 数组
    if (key == Qt::Key_D) key[0] = true;
    if (key == Qt::Key_F) key[1] = true;
    if (key == Qt::Key_J) key[2] = true;
    if (key == Qt::Key_K) key[3] = true;

    // qDebug() << "Key Pressed: " << event->text() << " (" << key << ")";
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();

    // 更新 key[4] 数组
    if (key == Qt::Key_D) key[0] = false;
    if (key == Qt::Key_F) key[1] = false;
    if (key == Qt::Key_J) key[2] = false;
    if (key == Qt::Key_K) key[3] = false;

    // qDebug() << "Key Released: " << event->text() << " (" << key << ")";
}

bool* MainWindow::outputKey() {
    return key;
}

