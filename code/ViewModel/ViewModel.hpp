#ifndef VIEWMODEL_HPP
#define VIEWMODEL_HPP

#include <QObject>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include <windows.h>
#include "Song.hpp"
#include "Note.hpp"
#include "Key.hpp"
#include "../Common/NoteInfo.h"
#include "PlayThread.h"
#include "MusicThread.h"
#include <filesystem>

// 全局常量
const int LENGTH = 1440;
const int HEIGHT = 900;
const int LINE = 750;
const int LEFTEST_TRACK = 480;
const int WIDTH = 120;
const int NOTE_HEIGHT = 60;
const int TIME_INTERVAL = 16;
const int SPEED = 4;
const int PERFECT_TIME = 80;
const int GOOD_TIME = 120;

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
          song(Song("", "", 0, std::vector<Note>(), 0)),
          maxCombo(0),
          perfect(0),
          good(0),
          miss(0),
          accuracy(0.0),
          grade("")
    {}

    ~ViewModel() override {
        if (musicThread && musicThread->isRunning()) {
            musicThread->quit();
            musicThread->wait();
        }
        if (playThread && playThread->isRunning()) {
            playThread->quit();
            playThread->wait();
        }
    }

    std::vector<QString> select_songs() {
        std::vector<QString> filenames;
        for (const auto& entry : std::filesystem::directory_iterator("../resources/charts")) {
            if (entry.is_regular_file()) { // 不含后缀名
                filenames.push_back(QString::fromStdString(entry.path().stem().string()));
            }
        }
        return filenames;
    }

    void initialize(std::string songTitle) {
        title = std::move(songTitle);
        std::string songFile;
        songFile = "../resources/charts/" + title + ".json";
        pngPath = QString::fromStdString("../resources/covers/" + title + ".png");
        musicPath = QString::fromStdString("../resources/music/" + title + ".wav");
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
    }

    void play() {
        std::string songPath = "../resources/music/" + title + ".wav";

        musicThread = new MusicThread;
        musicThread->setPath(songPath);
        playThread = std::make_unique<PlayThread>(this);

        musicThread->start();
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
    void playtapsound();
    void showSettlement(QString title,int point,QString grade,double accuracy,int maxComb,int perfect,int good,int miss);

public slots:
    void startplay(std::string song) {
        initialize(song);
        play();
    }

    void dIsPressed() {
    // std::cout << "dIsPressed" << std::endl;
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
                continue;
            }
            if (y < 0) {
                break;
            }

            NoteInfo noteInfo = {x, y, i->visible};
            activeNotes.push_back(noteInfo);
        }
    }

    int updateKeyStates() {
        int result = 4;
        bool result1 = false;
        for (int j = 0; j < 4; ++j) {
            result1 = keys[j].updateState(keyFromView[j]);
            // std::cout << "result1: " << result1 << std::endl;
            if (result1 && result == 4) {
                result = j;
                break;
            }
        }
        return result;
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
    QString musicPath;
    std::string* pngPathPtr;

    //varialbes for Settlement Interface
    int maxCombo;
    int perfect;
    int good;
    int miss;
    double accuracy;
    QString grade;

    MusicThread* musicThread;
    std::unique_ptr<PlayThread> playThread;
};


#endif // VIEWMODEL_HPP