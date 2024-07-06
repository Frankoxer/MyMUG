#include <QApplication>
#include <QPushButton>

#include "code/App/GameApp.h"
#include "code/View/mainwindow.h"
#include "code/ViewModel/ViewModel.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ViewModel viewModel;
    MainWindow window;
    GameApp gameApp(&window, &viewModel);
    gameApp.Init();

    return app.exec();
}
