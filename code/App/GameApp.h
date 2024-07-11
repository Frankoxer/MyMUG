//
// Created by Frankoxer on 24-7-6.
//

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "../ViewModel/ViewModel.hpp"
#include "../View/play/mainwindow.h"
#include "../View/select/selectwindow.h"
#include <memory>
#include <QApplication>
#include <QObject>

class GameApp : public QObject{
    Q_OBJECT
public:
    GameApp () {}
    void Init();

public slots:
    void startplay(QString song);
private:
    MainWindow *mainWindow;
    ViewModel *viewModel;
    SelectWindow *selectWindow;
};

#endif // GAMEAPP_H
