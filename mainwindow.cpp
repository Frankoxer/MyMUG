#include "mainwindow.h"
#include "ui_MainWindow.h"
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
    QPixmap backgroundPixmap(":/background.png"); // 使用资源路径加载图片
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
    int startY = 50;  // 音符的起始Y位置
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0; i < 4; ++i) {
        Note *note = new Note(tracks[i], i, currentTime + (i * 1000)); // 每个音符间隔1秒用于测试
        note->move(0, startY);
        notes.append(note);
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();
    QString keyText = event->text();
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

    if (!activeKeys.contains(key)) {
        // 创建新的 KeyEvent 对象并存储
        KeyEvent *keyEvent = new KeyEvent(key, keyText);
        keyEvent->setPressTime(timestamp);
        activeKeys.insert(key, keyEvent);
    }

    qDebug() << "Key Pressed: " << keyText << " (" << key << ") at " << timestamp;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();
    QString keyText = event->text();
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

    if (activeKeys.contains(key)) {
        // 更新 KeyEvent 对象的释放时间
        KeyEvent *keyEvent = activeKeys.value(key);
        keyEvent->setReleaseTime(timestamp);

        // 输出 KeyEvent 信息
        qDebug() << "Key Released: " << keyEvent->getKeyText() << " (" << keyEvent->getKey() << ")"
                 << "Pressed at: " << keyEvent->getPressTime()
                 << "Released at: " << keyEvent->getReleaseTime();

        // 删除 KeyEvent 对象
        delete keyEvent;
        activeKeys.remove(key);
    }
}
