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

void MainWindow::createNotes() {
    int startY = 100;  // 音符的起始Y位置
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0; i < 4; ++i) {
        noteBlock *note_in_scene = new noteBlock(tracks[i], i, currentTime + (i * 1000)); // 每个音符间隔1秒用于测试
        startY += 100;
        note_in_scene->move(0, startY);
        noteBlocks.append(note_in_scene);
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

//    int key = event->key();
//    QString keyText = event->text();
//    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

    int key = event->key();
    char keyContent = static_cast<char>(key);
    bool isPressed = true;
    std::chrono::time_point<std::chrono::steady_clock> gameStartTime = std::chrono::steady_clock::now();
    int pressTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(gameStartTime.time_since_epoch()).count();
    int releaseTimeStamp = 0;

    if (!activeKeys.contains(key)) {
        Key *keyObj = new Key(keyContent, isPressed, gameStartTime, pressTimeStamp, releaseTimeStamp);
        activeKeys.insert(key, keyObj);
    } else {
        activeKeys[key]->updateState(isPressed);
    }

    emit keyStateChanged(*activeKeys[key]);  // 发射信号，包含完整的Key对象


//    qDebug() << "Key Pressed: " << keyText << " (" << key << ") at " << timestamp;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();
    bool isPressed = false;

    if (activeKeys.contains(key)) {
        activeKeys[key]->updateState(isPressed);
        emit keyStateChanged(*activeKeys[key]);  // 发射信号，包含完整的Key对象

        qDebug() << "Key Released: " << event->text() << " (" << key << ")"
                 << "Pressed at: " << activeKeys[key]->getPressTimeStamp()
                 << "Released at: " << activeKeys[key]->getReleaseTimeStamp();

        delete activeKeys[key];
        activeKeys.remove(key);
    }
}
