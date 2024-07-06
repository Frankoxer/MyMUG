#ifndef VIEWMODEL_HPP
#define VIEWMODEL_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include "Song.hpp"
#include "Note.hpp"
#include "Key.hpp"

// 全局常量
const int LENGTH = 1440;
const int HEIGHT = 900;
const int LINE = 750;
const int LEFTEST_TRACK = 480;
const int WIDTH = 120;
const int NOTE_HEIGHT = 20;
const int TIME_INTERVAL = 16;
const int SPEED = 1;
const int PERFECT_TIME = 80;

// NoteInfo 结构体定义
typedef struct {
    int x;
    int y;
} NoteInfo;

class ViewModel {
public:
    ViewModel()
        : point(0),
          gameStartTime(std::chrono::steady_clock::now()),
          keyFromViewPtr(nullptr),
          activeNotesPtr(nullptr) {}

    void initialize(const std::string& songFile, bool* keyFromView, std::vector<NoteInfo>* activeNotes) {
        std::ifstream file(songFile);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        song = std::make_unique<Song>(file);
        song->ShowSong();
        notes = song->getNotes();
        if (notes.empty()) {
            throw std::runtime_error("No notes in the song");
        }

        gameStartTime = std::chrono::steady_clock::now();
        keys[0] = Key('d', false, gameStartTime, 0, 0);
        keys[1] = Key('f', false, gameStartTime, 0, 0);
        keys[2] = Key('j', false, gameStartTime, 0, 0);
        keys[3] = Key('k', false, gameStartTime, 0, 0);

        keyFromViewPtr = keyFromView;
        activeNotesPtr = activeNotes;
    }

    void run() {
        auto it = notes.begin();
        while (true) {
            auto beforeLoopTime = std::chrono::steady_clock::now();

            updateNotes(it);
            updateKeyStates();
            checkHits();

            auto afterLoopTime = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_INTERVAL) - (afterLoopTime - beforeLoopTime));
            if ((afterLoopTime - gameStartTime).count() > song->getEndTime()) {
                break;
            }
        }
    }

private:
    void updateNotes(std::vector<Note>::iterator& it) {
        auto currentTime = std::chrono::steady_clock::now();
        auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
        activeNotesPtr->clear();

        for (auto i = it; i != notes.end(); ++i) {
            int x = i->getTrack() * WIDTH / 4 + LEFTEST_TRACK;
            int y = SPEED * timePassed + LINE - i->getTimestamp() * SPEED;

            if (y > HEIGHT) {
                it = i + 1;
            }
            if (y < 0) {
                break;
            }

            NoteInfo noteInfo = {x, y};
            activeNotesPtr->push_back(noteInfo);
        }
    }

    void updateKeyStates() {
        for (int j = 0; j < 4; ++j) {
            keys[j].updateState(keyFromViewPtr[j]);
        }
    }

    void checkHits() {
        auto currentTime = std::chrono::steady_clock::now();
        int currentTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();

        for (auto i = activeNotesPtr->begin(); i != activeNotesPtr->end(); ++i) {
            if (i->y > LINE - NOTE_HEIGHT && i->y < LINE) {
                switch (i->x) {
                    case 480:
                        if (isPerfectHit(keys[0], currentTimeStamp)) {
                            point += 100;
                        }
                        break;
                    case 600:
                        if (isPerfectHit(keys[1], currentTimeStamp)) {
                            point += 100;
                        }
                        break;
                    case 720:
                        if (isPerfectHit(keys[2], currentTimeStamp)) {
                            point += 100;
                        }
                        break;
                    case 840:
                        if (isPerfectHit(keys[3], currentTimeStamp)) {
                            point += 100;
                        }
                        break;
                }
            } else {
                break;
            }
        }
    }

    bool isPerfectHit(const Key& key, int currentTimeStamp) {
        return key.getPressTimeStamp() - currentTimeStamp <= PERFECT_TIME &&
               key.getReleaseTimeStamp() >= currentTimeStamp - PERFECT_TIME;
    }

    int point;
    std::unique_ptr<Song> song;
    std::vector<Note> notes;
    std::chrono::time_point<std::chrono::steady_clock> gameStartTime;
    Key keys[4];
    bool* keyFromViewPtr;
    std::vector<NoteInfo>* activeNotesPtr;
};


#endif // VIEWMODEL_HPP