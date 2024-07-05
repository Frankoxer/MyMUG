#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "Song.hpp"
#include "Note.hpp"
#include "Key.hpp"

//size of window
int LENGTH=1440;
int HEIGHT=900;
int line=750;

//x of the leftest track
int leftestTrack=480;

//width of the track
int width=120;
int noteHeight=20;

//time interval between each frame
int time_interval=16;

//speed of the note
int speed=1;//实际是1/5

int point=0;//得分

//
int perfectTime=80;

//the keys from view
bool keyFromView[4] = {false, false, false, false};

typedef struct {
    int x;
    int y;
} NoteInfo;



int main0(void)
{
    // 从文件中读取歌曲信息并创建歌曲对象
    std::ifstream file("Chronostasis.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    Song song(file);
    song.ShowSong();

    //get note vector
    std::vector<Note> notes = song.getNotes();
    if (notes.empty()) {
        std::cerr << "No notes in the song" << std::endl;
        return 1;
    }

    std::vector<NoteInfo> activeNotes;//需要被显示在windows上的所有note
    auto gameStartTime = std::chrono::steady_clock::now();//when the game begin
    Key keys[4] = {Key('d',false,gameStartTime,0,0), Key('f',false,gameStartTime,0,0), Key('j',false,gameStartTime,0,0), Key('k',false,gameStartTime,0,0)};
    std::vector<Note>::iterator it=notes.begin();

    while (true) {
        auto beforeLoopTime = std::chrono::steady_clock::now();//time before the loop begin

        for(auto i=it; i!=notes.end(); i++){
            //get the time passed since the game begin
            auto currentTime = std::chrono::steady_clock::now();
            auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();

            //get the position of the note
            int x = i->getTrack() * width / 4+leftestTrack;
            //get the y of the note
            int y = speed* timePassed + line- i->getTimestamp()*speed;

            //if the note is out of the window, break
            if(y>HEIGHT){
                //update it to the next note on the screen
                it=i+1;
            }
            if(y<0){
                break;
            }

            //if the note is in the window, add it to the activeNotes
            NoteInfo noteInfo = {x, y};
            activeNotes.push_back(noteInfo);
        }

        //update the state of the keys
        for(int j=0; j<4; j++){
            keys[j].updateState(keyFromView[j]);
        }

        //check if the note is hit
        //实际上只需要检查activeNotes中的元素就足够了，无需检查其他的
        for(auto i=activeNotes.begin(); i!=activeNotes.end(); i++){
            auto currentTime = std::chrono::steady_clock::now();
            int currentTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();

            //if the note should be hit
            if(i->y>line-noteHeight && i->y<line){
                switch(i->x){
                    case 480:
                        if(keys[0].getPressTimeStamp()-currentTimeStamp<=perfectTime && keys[0].getReleaseTimeStamp()>=currentTimeStamp-perfectTime){
                            point+=100;
                        }
                        break;
                    case 600:
                        if(keys[1].getPressTimeStamp()-currentTimeStamp<=perfectTime && keys[1].getReleaseTimeStamp()>=currentTimeStamp-perfectTime){
                            point+=100;
                        }
                        break;
                    case 720:
                        if(keys[2].getPressTimeStamp()-currentTimeStamp<=perfectTime && keys[2].getReleaseTimeStamp()>=currentTimeStamp-perfectTime){
                            point+=100;
                        }
                        break;
                    case 840:
                        if(keys[3].getPressTimeStamp()-currentTimeStamp<=perfectTime && keys[3].getReleaseTimeStamp()>=currentTimeStamp-perfectTime){
                            point+=100;
                        }
                        break;
                }
            }
            else break;

        }

        auto afterLoopTime = std::chrono::steady_clock::now();//time after the loop begin
        std::this_thread::sleep_for(std::chrono::milliseconds(time_interval) - (afterLoopTime - beforeLoopTime));
        if((afterLoopTime - gameStartTime).count() > song.getEndTime()){
            break;//if the game is over, break
        }
    }

    return 0;
}

//#include "ViewModel.h"
//#include <QThread>
//#include <iostream>
//#include <fstream>
//#include <chrono>
//#include <thread>
//
//// 修改构造函数
//ViewModel::ViewModel(const std::string &songFilePath, QObject *parent)
//        : QObject(parent),
//          song([&]() -> Song {
//              std::ifstream file(songFilePath);
//              if (!file.is_open()) {
//                  throw std::runtime_error("Failed to open file");
//              }
//              return Song(file);
//          }()),  // 使用 lambda 初始化 Song
//          keys{Key('d', false, gameStartTime, 0, 0),
//               Key('f', false, gameStartTime, 0, 0),
//               Key('j', false, gameStartTime, 0, 0),
//               Key('k', false, gameStartTime, 0, 0)}
//{
//    song.ShowSong();
//    gameStartTime = std::chrono::steady_clock::now();
//    std::vector<Note> notes = song.getNotes();  // 假设你有对song的访问权限
//    it = notes.begin();
//}
//
//void ViewModel::updateKeys(const QVector<bool> &keys) {
//    for (int i = 0; i < 4; ++i) {
//        keyFromView[i] = keys[i];
//    }
//}
//
//void ViewModel::runGame() {
//    while (true) {
//        auto beforeLoopTime = std::chrono::steady_clock::now();
//        processNotes();
//        for (int j = 0; j < 4; ++j) {
//            keys[j].updateState(keyFromView[j]);
//        }
//        checkNoteHit();
//        auto afterLoopTime = std::chrono::steady_clock::now();
//        std::this_thread::sleep_for(std::chrono::milliseconds(time_interval) - (afterLoopTime - beforeLoopTime));
//        if (std::chrono::duration_cast<std::chrono::milliseconds>(afterLoopTime - gameStartTime).count() > song.getEndTime()) {
//            break;
//        }
//    }
//}
//
//void ViewModel::processNotes() {
//    for (auto i = it; i != song.getNotes().end(); ++i) {
//        auto currentTime = std::chrono::steady_clock::now();
//        auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
//        int x = i->getTrack() * width / 4 + leftestTrack;
//        int y = speed * timePassed + line - i->getTimestamp() * speed;
//        if (y > HEIGHT) {
//            it = i + 1;
//        }
//        if (y < 0) {
//            break;
//        }
//        NoteInfo noteInfo = {x, y};
//        activeNotes.push_back(noteInfo);
//    }
//}
//
//void ViewModel::checkNoteHit() {
//    auto currentTime = std::chrono::steady_clock::now();
//    int currentTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
//    for (auto i = activeNotes.begin(); i != activeNotes.end(); ++i) {
//        if (i->y > line - noteHeight && i->y < line) {
//            switch (i->x) {
//                case 480:
//                    if (keys[0].getPressTimeStamp() - currentTimeStamp <= perfectTime && keys[0].getReleaseTimeStamp() >= currentTimeStamp - perfectTime) {
//                        point += 100;
//                    }
//                    break;
//                case 600:
//                    if (keys[1].getPressTimeStamp() - currentTimeStamp <= perfectTime && keys[1].getReleaseTimeStamp() >= currentTimeStamp - perfectTime) {
//                        point += 100;
//                    }
//                    break;
//                case 720:
//                    if (keys[2].getPressTimeStamp() - currentTimeStamp <= perfectTime && keys[2].getReleaseTimeStamp() >= currentTimeStamp - perfectTime) {
//                        point += 100;
//                    }
//                    break;
//                case 840:
//                    if (keys[3].getPressTimeStamp() - currentTimeStamp <= perfectTime && keys[3].getReleaseTimeStamp() >= currentTimeStamp - perfectTime) {
//                        point += 100;
//                    }
//                    break;
//            }
//        }
//    }
//}
