#ifndef MYMUG_MAINWINDOW_H
#define MYMUG_MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QVector>
#include "track.h"
#include "noteBlock.h"
#include "KeyEvent.h"
#include "judgementLine.h"
#include "ComboBlock.h"
#include "ScoreBlock.h"
#include "scoreTitleBlock.h"
#include "backgroundBlock.h"
#include "albumBlock.h"
#include "levelBlock.h"
#include "accuracyBlock.h"
#include "maxComboBlock.h"
#include "performListBlock.h"
#include "ScoreEnd.h"
#include "../Common/Key.hpp"
#include "../Common/NoteInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    bool* outputKey(); // 返回bool指针
    void setActiveNotes(std::vector<NoteInfo> *activeNotesPtr) {activeNotes = activeNotesPtr;} // 设置activeNotes
    void recieveActiveNotes(std::vector<NoteInfo> *activeNotesPtr);
    std::vector<NoteInfo>* getActiveNotes() const { return activeNotes; }


public slots:
    // 游戏运行中
    void updateNotes();
    void updateScore(int score);
    void updateCombo(int combo);
    void createBackground(const QString &pngPath);
    void createScoreTitleBlock(const QString &title);
    void createTracks();
    void createJudgementLine();
    void playtapsound();
    // 结算
    void showResults(QString title, int point, QString grade, double accuracy, int maxCombo, int perfect, int good, int miss);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void keyStateChanged(const Key &key);
    void key0Pressed();
    void key1Pressed();
    void key2Pressed();
    void key3Pressed();
    void key0Released();
    void key1Released();
    void key2Released();
    void key3Released();

private:
    Ui::MainWindow *ui;
    QMap<int, Key*> activeKeys;  // 存储正在按下的键
    QList<Track*> tracks;
    JudgementLine *judgementLine = nullptr;
    QList<noteBlock*> noteBlocks;
    std::vector<NoteInfo> *activeNotes;  // 用于存储activeNotesPtr
    ScoreBlock *scoreBlock = nullptr; // 游玩分数块
    ComboBlock *comboBlock = nullptr; // 游玩连击数块
    ScoreTitleBlock *scoreTitleBlock = nullptr; // 歌曲标题块
    backgroundBlock *background; // 背景块

    albumBlock *album;
    levelBlock *level;
    accuracyBlock *acc = nullptr;
    maxComboBlock *maxCom = nullptr;
    performListBlock *list = nullptr;
    ScoreEnd *scoreEnd = nullptr;


    void createComboBlock(int combo);
    void createScoreBlock(int score);
    void createNotes();
    // 结算
    void createBackground_end(const QString &pngPath);
    void createScoreBlock_end(int score);
    void createScoreTitleBlock_end(const QString &title);
    void createComboBlock_end(int combo);
    void createLevel_end(const QString& level_char);
    void createAlbum_end(const QString &pngPath);
    void createAccuracy_end(double accuracy);
    void createMaxCombo_end(int maxCombo);
    void createPerformList_end(int perfect, int good, int miss);
};

#endif //MYMUG_MAINWINDOW_H
