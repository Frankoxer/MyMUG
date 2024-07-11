//
// Created by Frankoxer on 24-7-11.
//

#include "MusicThread.h"
#include <iostream>

void MusicThread::run() {
    std::cout << "MusicThread running: " << songPathChar << std::endl;
    PlaySound(TEXT(songPathChar.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
}