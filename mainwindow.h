#ifndef MYMUG_MAINWINDOW_H
#define MYMUG_MAINWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMap>
#include "track.h"
#include "note.h"
#include "keyevent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;
    QMap<int, KeyEvent*> activeKeys;  // 存储正在按下的键
    QList<Track*> tracks;
    QList<Note*> notes;

    void createTracks();
    void createNotes();
};

#endif //MYMUG_MAINWINDOW_H
