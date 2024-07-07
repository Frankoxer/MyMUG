//
// Created by Frankoxer on 24-7-6.
//

#include "GameApp.h"
#include <stdio.h>
#include <filesystem>

void GameApp::Init() {

    MainWindow *mainWindow = new MainWindow();
    ViewModel *viewModel = new ViewModel();

    connect(viewModel, &ViewModel::updateView, mainWindow, &MainWindow::updateView);
    connect(viewModel, &ViewModel::updateScore, mainWindow, &MainWindow::updateScore);
    connect(viewModel, &ViewModel::createBackground, mainWindow, &MainWindow::createBackground);
    connect(viewModel, &ViewModel::createTracks, mainWindow, &MainWindow::createTracks);
    connect(viewModel, &ViewModel::createJudgementLine, mainWindow, &MainWindow::createJudgementLine);
    mainWindow->show();
    viewModel->initialize("Chronostasis", mainWindow->outputKey());
    mainWindow->setActiveNotes(viewModel->getActiveNotes());


    viewModel->startGame();

}