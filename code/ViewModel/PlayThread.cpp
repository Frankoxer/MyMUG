//
// Created by Frankoxer on 24-7-6.
//

#include "PlayThread.h"
#include "ViewModel.hpp" // 在这里包含ViewModel的定义

PlayThread::PlayThread(ViewModel* viewModel) : viewModel(viewModel) {}

void PlayThread::run() {
    if (viewModel) {
        viewModel->run();
    }
}