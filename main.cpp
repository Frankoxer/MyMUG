#include <QApplication>
#include <QPushButton>

#include "code/App/GameApp.h"
#include "code/View/play/mainwindow.h"
#include "code/ViewModel/ViewModel.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GameApp gameApp;
    gameApp.Init();

    return app.exec();
}
