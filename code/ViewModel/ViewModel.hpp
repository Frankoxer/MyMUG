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
          comb(0),
          gameStartTime(std::chrono::steady_clock::now()),
          activeNotesPtr(nullptr),
          pointPtr(nullptr),
          titlePtr(nullptr),
          pngPathPtr(nullptr),
          song(Song("", "", 0, std::vector<Note>(), 0)) {}

    void initialize(const std::string& songTitle) {
        title = songTitle;
        std::string songFile;
        songFile = "../resources/charts/" + title + ".json";
        // pngPath = "../resources/covers/" + title + ".png";
        pngPath = QString::fromStdString("../resources/covers/" + title + ".png");
        emit createBackground(pngPath);
        emit createTracks();
        emit createJudgementLine();
        emit createTitleBlock(QString::fromStdString(title));
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

        activeNotesPtr = &activeNotes;
        pointPtr = &point;
        titlePtr = &title;
        // pngPathPtr = &pngPath;
    }

    // void run() {
    //     auto it = notes.begin();
    //     std::string songPath="";
    //     songPath+="../resources/music/" + title + ".wav";
    //     LPCSTR songPathChar = songPath.c_str();
    //     PlaySound(TEXT(songPathChar), NULL, SND_FILENAME | SND_ASYNC);
    //     gameStartTime = std::chrono::steady_clock::now();
    //
    //     for(auto it: keys) {
    //         it.updateStartTime(gameStartTime);
    //     }
    //
    //     while (true) {
    //         auto beforeLoopTime = std::chrono::steady_clock::now();
    //
    //         int isHit = 4;
    //         updateNotes(it);
    //         isHit = updateKeyStates();
    //         if(isHit != 4) {
    //             int track = isHit;
    //             auto currentTime = std::chrono::steady_clock::now();
    //             int currentTimeStamp = std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<1, 1000>>>(currentTime - gameStartTime).count();
    //
    //             for (auto i = notes.begin(); i != notes.end(); ++i) {
    //                 if (!i->isJudged && i->getTrack()==track+1 && abs(i->getTimestamp() - currentTimeStamp)<= PERFECT_TIME) {
    //                     point+= 100;
    //                     i->isJudged = true;
    //                     comb++;
    //                     emit updateCombo(comb);
    //                     emit updateScore(point);
    //                     // std::cout << "Score: " << point << std::endl;
    //                     break;
    //                 } else if (!i->isJudged && i->getTrack()==track+1 && abs(i->getTimestamp() - currentTimeStamp)<= GOOD_TIME) {
    //                     point+= 75;
    //                     comb++;
    //                     emit updateCombo(comb);
    //                     i->isJudged = true;
    //                     emit updateScore(point);
    //                     // std::cout << "Score: " << point << std::endl;
    //                     break;
    //                 }
    //             }
    //
    //         }
    //
    //         //Check if any note has passed the judgement line without being hit
    //         auto currentTime = std::chrono::steady_clock::now();
    //         int currentTimeStamp = std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<1, 1000>>>(currentTime - gameStartTime).count();
    //         for (auto i = notes.begin(); i != notes.end(); ++i) {
    //             if (!i->isJudged &&  currentTimeStamp - i->getTimestamp() > GOOD_TIME) {
    //                 comb = 0; // Reset the comb count when a note is missed
    //                 emit updateCombo(comb);
    //                 i->isJudged = true; // Mark the note as judged
    //                 break;
    //                 std::cout<<"Missed"<<std::endl;
    //             }
    //         }
    //
    //         // 检查是否到达乐曲结束时间，如果是，则退出循环
    //         currentTime = std::chrono::steady_clock::now();
    //         auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
    //         if (elapsedTime > song.getEndTime()) {
    //             std::cout << "Song ended. Exiting game loop." << std::endl;
    //             break;
    //         }
    //         if(activeNotesPtr == nullptr) {
    //             std::cout << "activeNotesPtr is nullptr" << std::endl;
    //         }
    //         auto afterLoopTime = std::chrono::steady_clock::now();
    //         std::this_thread::sleep_for(std::chrono::milliseconds(TIME_INTERVAL) - (afterLoopTime - beforeLoopTime));
    //         emit updateNoteView();
    //     }
    // }

    void startGame() {
        auto *playThread = new PlayThread(this);
        playThread->start();
    }

    std::vector<NoteInfo>* getActiveNotes() const { return activeNotesPtr; }
    int* getPoint() const { return pointPtr; }
    std::string* getTitle() const { return titlePtr; }
    std::string* getPngPath() const { return pngPathPtr; }

signals:
    void updateNoteView();
    void updateScore(int newScore);
    void updateCombo(int newCombo);
    void createBackground(QString pngPath);
    void createTitleBlock(QString title);
    void createTracks();
    void createJudgementLine();

public slots:
    void dIsPressed() {
        keyFromView[0] = true;
    }

     void fIsPressed() {
        keyFromView[1] = true;
     }

     void jIsPressed() {
        keyFromView[2] = true;
     }

     void kIsPressed() {
        keyFromView[3] = true;
     }

    void dIsReleased() {
        keyFromView[0] = false;
    }

    void fIsReleased() {
        keyFromView[1] = false;
    }

    void jIsReleased() {
        keyFromView[2] = false;
    }

    void kIsReleased() {
        keyFromView[3] = false;
    }

public:
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

    int updateKeyStates() {
        int result = 4;
        bool result1= false;
        for (int j = 0; j < 4; ++j) {
            result1=keys[j].updateState(keyFromView[j]);
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

        for (auto & note : notes) {
            if (!note.isJudged && note.getTrack()==track+1 && std::abs(note.getTimestamp() - currentTimeStamp)<= PERFECT_TIME) {
                point+= 100;
                note.isJudged = true;
                emit updateScore(point);
                break;
            } else if (!note.isJudged && note.getTrack()==track+1 && std::abs(note.getTimestamp() - currentTimeStamp)<= GOOD_TIME) {
                point+= 75;
                note.isJudged = true;
                emit updateScore(point);
                break;
            }
        }
    }

    int point;
    int comb;
    Song song;
    bool keyFromView[4] = {false, false, false, false};
    std::vector<Note> notes;
    std::chrono::time_point<std::chrono::steady_clock> gameStartTime;
    Key keys[4];
    std::vector<NoteInfo> activeNotes;
    std::vector<NoteInfo>* activeNotesPtr;
    int* pointPtr;
    std::string title;
    std::string* titlePtr;
    QString pngPath;
    std::string* pngPathPtr;
};


#endif // VIEWMODEL_HPP