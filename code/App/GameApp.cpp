//
// Created by Frankoxer on 24-7-6.
//

#include "GameApp.h"
#include <stdio.h>
#include <filesystem>

void GameApp::Init() {

    MainWindow *mainWindow = new MainWindow();
    ViewModel *viewModel = new ViewModel();

    connect(viewModel, &ViewModel::updateNoteView, mainWindow, &MainWindow::updateNotes);
    connect(viewModel, &ViewModel::updateScore, mainWindow, &MainWindow::updateScore);
    connect(viewModel, &ViewModel::updateCombo, mainWindow, &MainWindow::updateCombo);
    connect(viewModel, &ViewModel::createBackground, mainWindow, &MainWindow::createBackground);
    connect(viewModel, &ViewModel::createTracks, mainWindow, &MainWindow::createTracks);
    connect(viewModel, &ViewModel::createTitleBlock, mainWindow, &MainWindow::createScoreTitleBlock);
    connect(viewModel, &ViewModel::createJudgementLine, mainWindow, &MainWindow::createJudgementLine);
    connect(mainWindow, &MainWindow::key0Pressed, viewModel, &ViewModel::dIsPressed);
    connect(mainWindow, &MainWindow::key1Pressed, viewModel, &ViewModel::fIsPressed);
    connect(mainWindow, &MainWindow::key2Pressed, viewModel, &ViewModel::jIsPressed);
    connect(mainWindow, &MainWindow::key3Pressed, viewModel, &ViewModel::kIsPressed);
    connect(mainWindow, &MainWindow::key0Released, viewModel, &ViewModel::dIsReleased);
    connect(mainWindow, &MainWindow::key1Released, viewModel, &ViewModel::fIsReleased);
    connect(mainWindow, &MainWindow::key2Released, viewModel, &ViewModel::jIsReleased);
    connect(mainWindow, &MainWindow::key3Released, viewModel, &ViewModel::kIsReleased);

    mainWindow->show();
    viewModel->initialize("Cyaegha");
    mainWindow->setActiveNotes(viewModel->getActiveNotes());


    viewModel->startGame();

}