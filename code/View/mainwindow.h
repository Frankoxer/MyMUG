#ifndef MYMUG_MAINWINDOW_H
#define MYMUG_MAINWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMap>
#include "../../include/track.h"
#include "../../include/noteBlock.h"
#include "../../include/KeyEvent.h"
#include "code/Key.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    bool* outputKey(); // 返回bool指针

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void keyStateChanged(const Key &key);

private:
    Ui::MainWindow *ui;
    QMap<int, Key*> activeKeys;  // 存储正在按下的键
    QList<Track*> tracks;
    QList<noteBlock*> noteBlocks;
    std::vector<NoteInfo> *activeNotes;  // 用于存储activeNotesPtr
    bool key[4] = {false, false, false, false};  // 用于保存按键状态

    void createTracks();
    void createNotes();
};

#endif //MYMUG_MAINWINDOW_H
