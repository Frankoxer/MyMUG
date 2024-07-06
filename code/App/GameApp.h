//
// Created by Frankoxer on 24-7-6.
//

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "../ViewModel/ViewModel.hpp"
#include "../View/mainwindow.h"
#include <memory>
#include <QApplication>
#include <QObject>

class GameApp : public QObject{
    Q_OBJECT
public:
    GameApp (MainWindow *mainWindow, ViewModel *viewModel) : mainWindow(mainWindow), viewModel(viewModel) {}
    void Init();
private:
    MainWindow *mainWindow;
    ViewModel *viewModel;
};

#endif // GAMEAPP_H
