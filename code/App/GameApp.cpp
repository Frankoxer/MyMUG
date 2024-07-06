//
// Created by Frankoxer on 24-7-6.
//

#include "GameApp.h"
#include <stdio.h>
#include <filesystem>

void GameApp::Init() {

    mainWindow->show();
    // viewModel->initialize("E:/course/c++/MyMUG/resources/charts/Chronostasis.json", mainWindow->outputKey());
    // std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    viewModel->initialize("../resources/charts/Chronostasis.json", mainWindow->outputKey());
    mainWindow->setActiveNotes(viewModel->getActiveNotes());
    printf("%p\n", viewModel->getActiveNotes());
    printf("%p\n", mainWindow->getActiveNotes());
    connect(viewModel, &ViewModel::updateView, mainWindow, &MainWindow::updateView);

    viewModel->startGame();
    // mainWindow->render();
}