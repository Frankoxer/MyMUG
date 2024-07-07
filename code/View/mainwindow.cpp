#include "mainwindow.h"
#include "ui_MainWindow.h"
// #include "D:\eclipse_workspace\cpp_in_CLION\MyMUG\cmake-build-debug\MyMUG_autogen\include\ui_MainWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDateTime>
#include <iostream>
#include <chrono>

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
    // QLabel *backgroundLabel = new QLabel(this);
    // backgroundLabel->setGeometry(0, 0, 1440, 900);  // 设置 QLabel 大小与窗口一致
//    QPixmap backgroundPixmap(":/background.png"); // 使用资源路径加载图片


    // createBackground();
    // 创建音轨和音符
    // createTracks();
    // 创建判定线
    // createJudgementLine();
    // 创建空的分数块
    scoreBlock = new ScoreBlock(this);
    scoreBlock->setScore(0);
    scoreBlock->move(1140, 200);
    scoreBlock->show();
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
//QString path
void MainWindow::createBackground(const QString &pngPath) {
//    QPixmap backgroundPixmap("../resources/covers/Chronostasis.png"); // 使用资源路径加载图片
//    QPixmap backgroundPixmap("path"); // 使用资源路径加载图片
//    backgroundLabel->setPixmap(backgroundPixmap);
//    backgroundLabel->setScaledContents(true);  // 使图片缩放填满整个 QLabel
//    backgroundLabel->lower();  // 将 QLabel 放置在底层
    std::cout << "MainWindow::create background" << std::endl;
    background = new backgroundBlock(this);
    background->setBackgroundPath(pngPath);
    background->move(0, 0);
    background->show();
}


void MainWindow::createTracks() {
    int startX = 480;  // 起始 X 位置
    int gap = 120;     // 轨道间距

    for (int i = 0; i < 4; ++i) {
        Track *track = new Track(this);
        track->move(startX + i * gap, 0);
        tracks.append(track);
        track->show();
    }
}

void MainWindow::createJudgementLine(){
    JudgementLine *judgementLine = new JudgementLine(this);
    judgementLine->move(480, 750);
    judgementLine->show();
}



void MainWindow::recieveActiveNotes(std::vector<NoteInfo> *activeNotesPtr) {
    this->activeNotes = activeNotesPtr;
}

void MainWindow::createNotes() {
    if (activeNotes == nullptr)   // 确保activeNotes指针有效
    {
        int startY = 100;
        // std::cout << "First iter" << std::endl;
        for(int i = 0;i < 4; ++i) {
            noteBlock *note = new noteBlock(tracks[i], i, startY);
            note->move(0, startY);
            noteBlocks.append(note);

        }
        std::cout << noteBlocks.size() << std::endl;
    }else {
        // noteBlocks.clear();
        qDeleteAll( noteBlocks );
        noteBlocks.clear();
        for ( auto noteInfo : *activeNotes ) {
            int trackIndex = (noteInfo.x / 120) - 4; // 计算轨道索引
            // std::cout << "trackIndex: " << trackIndex << std::endl;
            noteBlock *note = new noteBlock(tracks[trackIndex], trackIndex, noteInfo.y);
            // std::cout << noteInfo.y << std::endl;
            note->move(0 ,noteInfo.y);
            noteBlocks.append(note);
            note->show();
        }
        // std::cout << noteBlocks.size() << std::endl;
    }
    update();
}

void MainWindow::createComboBlock() {
    ComboBlock *Combo = new ComboBlock(this);
    Combo->move(0, 0);
    Combo->show();
}

void MainWindow::createScoreBlock(int score) {
    // 先把原来的分数块删除
    if (scoreBlock != nullptr) {
        scoreBlock->hide();
        // std::cout << "delete scoreBlock" << std::endl;
        delete scoreBlock;
        scoreBlock = nullptr;
    }
    // std::cout << "create scoreBlock" << std::endl;
    scoreBlock = new ScoreBlock(this);
    scoreBlock->setScore(score);
    scoreBlock->move(1140, 200);
    scoreBlock->show();
}

void MainWindow::createScoreTitleBlock() {
    ScoreTitleBlock *scoreTitleBlock = new ScoreTitleBlock(this); // Create a new ScoreTitleBlock object
    scoreTitleBlock->move(1140, 850); // Move the block to the specified position (x=1340, y=0)
    scoreTitleBlock->setTitle("hobby"); // Set the title for the block
    scoreTitleBlock->show(); // Display the block
}

void MainWindow::updateView() {
    // 重新创建音符
//    createBackground();
    createNotes();
    // createComboBlock();
    // createScoreBlock();
    // createScoreTitleBlock();
    // createTracks();
}

void MainWindow::updateScore(int newScore) {
    // 更新分数
    // std::cout << __FUNCTION__ << " " << newScore << std::endl;
    createScoreBlock(newScore);
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

    // 输出当前时间戳
    // auto now = std::chrono::steady_clock::now(); // 获取当前系统时间
    // auto duration = now.time_since_epoch(); // 从1970-01-01 00:00:00 UTC到现在的持续时间
    // auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count(); // 将持续时间转换为毫秒
    //
    // std::cout << millis << std::endl; // 输出毫秒数
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

