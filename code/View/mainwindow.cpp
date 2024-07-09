#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QDateTime>
#include <iostream>
#include <chrono>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 设置固定窗口大小
    setFixedSize(1440, 900);

    // scoreBlock = new ScoreBlock(this);
    // scoreBlock->setScore(0);
    // scoreBlock->move(1140, 200);
    // scoreBlock->show();
    //
    // comboBlock = new ComboBlock(this);
    // comboBlock->setCombo(0);
    // comboBlock->move(0, 0);
    // comboBlock->show();

}

MainWindow::~MainWindow() {
    delete ui;

    // 清理 activeKeys 中的 KeyEvent 对象
    qDeleteAll(activeKeys);
    activeKeys.clear();
}

//QString path
void MainWindow::createBackground(const QString &pngPath) {
    background = new backgroundBlock(this);
    background->setBackgroundPath(pngPath);
    background->move(0, 0);
    background->show();
}

void MainWindow::createTracks() {
    int startX = 480;  // 起始 X 位置
    int gap = 120;     // 轨道间距

    for (int i = 0; i < 4; ++i) {
        auto *track = new Track(this);
        track->move(startX + i * gap, 0);
        tracks.append(track);
        track->show();
    }
}

void MainWindow::createJudgementLine(){
    auto *judgementLine = new JudgementLine(this);
    judgementLine->move(480, 770);
    judgementLine->show();
}


void MainWindow::recieveActiveNotes(std::vector<NoteInfo> *activeNotesPtr) {
    this->activeNotes = activeNotesPtr;
}

void MainWindow::createNotes() {
    if (activeNotes == nullptr)   // 确保activeNotes指针有效
    {
        int startY = 100;
        for(int i = 0;i < 4; ++i) {
            auto *note = new noteBlock(tracks[i], i, startY);
            note->move(0, startY);
            noteBlocks.append(note);
        }
    }else {
        qDeleteAll( noteBlocks );
        noteBlocks.clear();
        for ( auto noteInfo : *activeNotes ) {
            if(noteInfo.visible) {
                int trackIndex = (noteInfo.x / 120) - 4; // 计算轨道索引
                auto *note = new noteBlock(tracks[trackIndex], trackIndex, noteInfo.y);
                note->move(0 ,noteInfo.y);
                noteBlocks.append(note);
                note->show();
            }

        }
    }
    update();
}

void MainWindow::createComboBlock(int combo) {
    // 先把原来的连击块删除

        // comboBlock->hide();

    if(comboBlock != nullptr) {
        delete comboBlock;
        comboBlock = nullptr; // Prevent double deletion and invalid access
    }
        // comboBlock = nullptr;

    if(combo == 0) return ;
    comboBlock = new ComboBlock(this);
    comboBlock->setCombo(combo);
    comboBlock->move(150, 300);
    comboBlock->show();
}

void MainWindow::createScoreBlock(int score) {
    // 先把原来的分数块删除

    if(scoreBlock != nullptr) {
        delete scoreBlock;
        scoreBlock = nullptr; // Prevent double deletion and invalid access
    }
        // scoreBlock->hide(


    scoreBlock = new ScoreBlock(this);
    scoreBlock->setScore(score);
    scoreBlock->move(1300, 0);
    scoreBlock->show();
}

void MainWindow::createScoreTitleBlock(const QString &title) {
    auto *scoreTitleBlock = new ScoreTitleBlock(this); // Create a new ScoreTitleBlock object
    scoreTitleBlock->move(1090, 830); // Move the block to the specified position (x=1340, y=0)
    scoreTitleBlock->setTitle(title); // Set the title for the block
    scoreTitleBlock->show(); // Display the block
}

void MainWindow::updateNotes() {
    // 重新创建音符
    createNotes();
}

void MainWindow::updateScore(int newScore) {
    // 更新分数
    createScoreBlock(newScore);
}

void MainWindow::updateCombo(int newCombo) {
    // 更新连击数
    createComboBlock(newCombo);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();

    // 更新 keyFromView[4] 数组并发射信号
    if (key == Qt::Key_D) {
        // std::cout << "Key D Pressed" << std::endl;
        emit key0Pressed();
    }
    if (key == Qt::Key_F) {
        emit key1Pressed();
    }
    if (key == Qt::Key_J) {
        emit key2Pressed();
    }
    if (key == Qt::Key_K) {
        emit key3Pressed();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;  // 忽略自动重复事件

    int key = event->key();

    // 更新 keyFromView[4] 数组并发射信号
    if (key == Qt::Key_D) {
        emit key0Released();
    }
    if (key == Qt::Key_F) {
        emit key1Released();
    }
    if (key == Qt::Key_J) {
        emit key2Released();
    }
    if (key == Qt::Key_K) {
        emit key3Released();
    }
}
