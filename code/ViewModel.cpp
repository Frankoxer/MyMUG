#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include "Song.hpp"
#include "Note.hpp"

//size of window
int LENGTH=1440;
int leftestTrack=480;//x of the leftest track
int width=120;//width of the track
int HEIGHT=900;
int line=750;
//time interval between each frame
int time_interval=16;
//speed of the note
int speed=1;//实际是1/5


typedef struct {
    int x;
    int y;
} NoteInfo;

int main(void)
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

    std::vector<NoteInfo> activeNotes;
    auto gameStartTime = std::chrono::steady_clock::now();//when the game begin
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
            if(y>line){
                //update it to the next note
                it=i+1;
            }
            if(y<0){
                break;
            }

            //if the note is in the window, add it to the activeNotes
            NoteInfo noteInfo = {x, y};
            activeNotes.push_back(noteInfo);
        }


        auto afterLoopTime = std::chrono::steady_clock::now();//time after the loop begin
        if((afterLoopTime - gameStartTime).count() > song.getEndTime()){
            break;//if the game is over, break
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(time_interval) - (afterLoopTime - beforeLoopTime));
    }

    return 0;
}