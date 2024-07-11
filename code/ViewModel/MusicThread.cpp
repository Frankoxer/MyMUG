//
// Created by Frankoxer on 24-7-11.
//

#include "MusicThread.h"

void MusicThread::run() {
    PlaySound(TEXT(songPathChar), nullptr, SND_FILENAME | SND_ASYNC);
}