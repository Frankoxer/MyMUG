#ifndef VIEWMODEL_HPP
#define VIEWMODEL_HPP

#include <QObject>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <string>
#include <windows.h>
#include "Song.hpp"
#include "Note.hpp"
#include "../Common/Key.hpp"
#include "../Common/NoteInfo.h"
#include "PlayThread.h"

// 全局常量
const int LENGTH = 1440;
const int HEIGHT = 900;
const int LINE = 750;
const int LEFTEST_TRACK = 480;
const int WIDTH = 120;
const int NOTE_HEIGHT = 60;
const int TIME_INTERVAL = 16;
const int SPEED = 3;
const int PERFECT_TIME = 100;
const int GOOD_TIME = 150;

class ViewModel : public QObject{
    Q_OBJECT
public:
    // explicit ViewModel(QObject *parent = nullptr);
    ViewModel()
        : point(0),
          gameStartTime(std::chrono::steady_clock::now()),
          keyFromViewPtr(nullptr),
          activeNotesPtr(nullptr),
          pointPtr(nullptr),
          titlePtr(nullptr),
          pngPathPtr(nullptr),
          song(Song("", "", 0, std::vector<Note>(), 0)) {}

    void initialize(const std::string& songTitle, bool* keyFromView) {
        title = songTitle;
        std::string songFile="";
        songFile = "../resources/charts/" + title + ".json";
        // pngPath = "../resources/covers/" + title + ".png";
        pngPath = QString::fromStdString("../resources/covers/" + title + ".png");
        emit createBackground(pngPath);
        emit createTracks();
        emit createJudgementLine();
        std::ifstream file(songFile);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        song = Song(file);
        notes = song.getNotes();
        if (notes.empty()) {
            throw std::runtime_error("No notes in the song");
        }

        gameStartTime = std::chrono::steady_clock::now();
        keys[0] = Key('d', false, gameStartTime, 0, 0);
        keys[1] = Key('f', false, gameStartTime, 0, 0);
        keys[2] = Key('j', false, gameStartTime, 0, 0);
        keys[3] = Key('k', false, gameStartTime, 0, 0);

        keyFromViewPtr = keyFromView;
        activeNotesPtr = &activeNotes;
        pointPtr = &point;
        titlePtr = &title;
        // pngPathPtr = &pngPath;
    }

    void run() {
        auto it = notes.begin();
        std::string songPath="";
        songPath+="../resources/music/" + title + ".wav";
        LPCSTR songPathChar = songPath.c_str();
        PlaySound(TEXT(songPathChar), NULL, SND_FILENAME | SND_ASYNC);
        gameStartTime = std::chrono::steady_clock::now();

        for(auto it: keys) {
            it.updateStartTime(gameStartTime);
        }

        while (true) {
            auto beforeLoopTime = std::chrono::steady_clock::now();

            int isHit = 4;
            updateNotes(it);
            isHit = updateKeyStates();
            if(isHit != 4) checkHits(isHit);


            // 检查是否到达乐曲结束时间，如果是，则退出循环
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
            if (elapsedTime > song.getEndTime()) {
                std::cout << "Song ended. Exiting game loop." << std::endl;
                break;
            }
            if(activeNotesPtr == nullptr) {
                std::cout << "activeNotesPtr is nullptr" << std::endl;
            }
            auto afterLoopTime = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_INTERVAL) - (afterLoopTime - beforeLoopTime));
            emit updateView();
        }
    }

    void startGame() {
        PlayThread *playThread = new PlayThread(this);
        playThread->start();
    }

    std::vector<NoteInfo>* getActiveNotes() const { return activeNotesPtr; }
    int* getPoint() const { return pointPtr; }
    std::string* getTitle() const { return titlePtr; }
    std::string* getPngPath() const { return pngPathPtr; }

signals:
    void updateView();
    void updateScore(int newScore);
    void createBackground(const QString pngPath);
    void createTracks();
    void createJudgementLine();

private:
    void updateNotes(std::vector<Note>::iterator& it) {
        auto currentTime = std::chrono::steady_clock::now();
        auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
        activeNotes.clear();

        for (auto i = it; i != notes.end(); ++i) {
            int x = (i->getTrack()-1) * WIDTH + LEFTEST_TRACK;
            int y = SPEED * timePassed / 5 + LINE - i->getTimestamp() * SPEED / 5;

            if (y > HEIGHT) {
                it = i + 1;
            }
            if (y < 0) {
                break;
            }

            NoteInfo noteInfo = {x, y};
            activeNotes.push_back(noteInfo);
        }
    }

    // void updateKeyStates() {
    //     for (int j = 0; j < 4; ++j) {
    //         keys[j].updateState(keyFromViewPtr[j]);
    //     }
    // }
    //
    // void checkHits() {
    //     auto currentTime = std::chrono::steady_clock::now();
    //     int currentTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
    //
    //     for (auto i = activeNotes.begin(); i != activeNotes.end(); ++i) {
    //         if (i->y > LINE - NOTE_HEIGHT && i->y < LINE+NOTE_HEIGHT-20) {
    //             switch (i->x) {
    //                 case 480:
    //                     if (isPerfectHit(keys[0], currentTimeStamp)) {
    //                         point += 100;
    //                         std::cout << "Perfect hit in track 1!" << std::endl;
    //                     }
    //                     break;
    //                 case 600:
    //                     if (isPerfectHit(keys[1], currentTimeStamp)) {
    //                         point += 100;
    //                         std::cout << "Perfect hit in track 2!" << std::endl;
    //                     }
    //                     break;
    //                 case 720:
    //                     if (isPerfectHit(keys[2], currentTimeStamp)) {
    //                         point += 100;
    //                         std::cout << "Perfect hit in track 3!" << std::endl;
    //                     }
    //                     break;
    //                 case 840:
    //                     if (isPerfectHit(keys[3], currentTimeStamp)) {
    //                         point += 100;
    //                         std::cout << "Perfect hit in track 4!" << std::endl;
    //                     }
    //                     break;
    //             }
    //         } else {
    //             break;
    //         }
    //     }
    // }

    int updateKeyStates() {
        int result = 4;
        bool result1= false;
        for (int j = 0; j < 4; ++j) {
            result1=keys[j].updateState(keyFromViewPtr[j]);
            if (result1 && result==4) {
                result = j;
                break;
            }
        }
        return result;
    }

    void checkHits(int track) {
        auto currentTime = std::chrono::steady_clock::now();
        int currentTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();

        for (auto i = notes.begin(); i != notes.end(); ++i) {
            if (!i->isJudged && i->getTrack()==track+1 && std::abs(i->getTimestamp() - currentTimeStamp)<= PERFECT_TIME) {
                point+= 100;
                i->isJudged = true;
                emit updateScore(point);
                // std::cout << "Score: " << point << std::endl;
                break;
            } else if (!i->isJudged && i->getTrack()==track+1 && std::abs(i->getTimestamp() - currentTimeStamp)<= GOOD_TIME) {
                point+= 75;
                i->isJudged = true;
                emit updateScore(point);
                // std::cout << "Score: " << point << std::endl;
                break;
            }
        }
    }

    // bool isPerfectHit(const Key& key, int currentTimeStamp) {
    //     // return key.getPressTimeStamp() - currentTimeStamp <= PERFECT_TIME
    //     // &&
    //     //        key.getPressTimeStamp() >= currentTimeStamp - PERFECT_TIME
    //     // ;
    //     return std::abs(key.getPressTimeStamp() - currentTimeStamp) <= PERFECT_TIME;
    // }

    int point;
    Song song;
    std::vector<Note> notes;
    std::chrono::time_point<std::chrono::steady_clock> gameStartTime;
    Key keys[4];
    bool* keyFromViewPtr;
    std::vector<NoteInfo> activeNotes;
    std::vector<NoteInfo>* activeNotesPtr;
    int* pointPtr;
    std::string title;
    std::string* titlePtr;
    QString pngPath;
    std::string* pngPathPtr;
};


#endif // VIEWMODEL_HPP