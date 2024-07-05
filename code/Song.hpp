#ifndef SONG_HPP
#define SONG_HPP

//#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "Note.hpp"
#include <fstream>
#include "json.hpp" // 第三方 json 解析库

class Song {
public:
//    Song(std::string title, std::string artist, int bpm, const std::vector<Note>& notes, int endTime)
//        : title(std::move(title)), artist(std::move(artist)), bpm(bpm), notes(notes) ,endTime(endTime){}

    Song(std::ifstream &file); // 构造函数：从文件中读取歌曲信息并创建歌曲对象

    const std::string& getTitle() const { return title; }
    const std::string& getArtist() const { return artist; }
    int getBpm() const { return bpm; }
    const std::vector<Note>& getNotes() const { return notes; }
    int getEndTime() const { return endTime; }
    void ShowSong() const;

private:
    std::string title;
    std::string artist;
    int bpm;
    std::vector<Note> notes;
    int endTime;
};

Song::Song(std::ifstream &file) {
    nlohmann::json j;
    file >> j;
    title = j["title"];
    artist = j["artist"];
    bpm = j["bpm"];
    for (const auto& note : j["notes"]) {
        notes.emplace_back(note["timestamp"], note["track"], note["type"] == "Tap" ? Note::Tap : Note::Hold);
    }
    endTime = j["endTime"];
}

void Song::ShowSong () const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "BPM: " << bpm << std::endl;
    std::cout << "Notes: " << std::endl;
    for (const auto& note : notes) {
        std::cout << "Timestamp: " << note.getTimestamp() << " Track: " << note.getTrack() << " Type: " << (note.getType() == Note::Tap ? "Tap" : "Hold") << std::endl;
    }
}


#endif //SONG_H