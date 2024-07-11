//
// Created by Frankoxer on 24-7-6.
//

#include "GameApp.h"
#include <stdio.h>
#include <filesystem>
#include <utility>

void GameApp::Init() {

    auto *selectWindow = new SelectWindow();

    connect(selectWindow, &SelectWindow::startGame, this, &GameApp::startplay);

    std::vector<QString> songs;

    for (const auto& entry : std::filesystem::directory_iterator("../resources/charts")) {
        if (entry.is_regular_file()) { // 不含后缀名
            songs.push_back(QString::fromStdString(entry.path().stem().string()));
        }
    }
    selectWindow->setList(songs);
    selectWindow->show();
}

void GameApp::startplay(QString song) {

    MainWindow *mainWindow = new MainWindow();
    ViewModel *viewModel = new ViewModel();
    std::cout << song.toStdString() << std::endl;
    std::string songPath = song.toStdString();

    connect(viewModel, &ViewModel::updateNoteView, mainWindow, &MainWindow::updateNotes);
    connect(viewModel, &ViewModel::updateScore, mainWindow, &MainWindow::updateScore);
    connect(viewModel, &ViewModel::updateCombo, mainWindow, &MainWindow::updateCombo);
    connect(viewModel, &ViewModel::createBackground, mainWindow, &MainWindow::createBackground);
    connect(viewModel, &ViewModel::createTracks, mainWindow, &MainWindow::createTracks);
    connect(viewModel, &ViewModel::createTitleBlock, mainWindow, &MainWindow::createScoreTitleBlock);
    connect(viewModel, &ViewModel::createJudgementLine, mainWindow, &MainWindow::createJudgementLine);
    connect(viewModel, &ViewModel::playtapsound, mainWindow, &MainWindow::playtapsound);
    connect(viewModel, &ViewModel::showSettlement, mainWindow, &MainWindow::showResults);
    connect(mainWindow, &MainWindow::key0Pressed, viewModel, &ViewModel::dIsPressed);
    connect(mainWindow, &MainWindow::key1Pressed, viewModel, &ViewModel::fIsPressed);
    connect(mainWindow, &MainWindow::key2Pressed, viewModel, &ViewModel::jIsPressed);
    connect(mainWindow, &MainWindow::key3Pressed, viewModel, &ViewModel::kIsPressed);
    connect(mainWindow, &MainWindow::key0Released, viewModel, &ViewModel::dIsReleased);
    connect(mainWindow, &MainWindow::key1Released, viewModel, &ViewModel::fIsReleased);
    connect(mainWindow, &MainWindow::key2Released, viewModel, &ViewModel::jIsReleased);
    connect(mainWindow, &MainWindow::key3Released, viewModel, &ViewModel::kIsReleased);

    viewModel->initialize(songPath);
    mainWindow->show();
    mainWindow->setActiveNotes(viewModel->getActiveNotes());
    // delete selectWindow;
    viewModel->play();
}