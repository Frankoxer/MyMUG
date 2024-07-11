#ifndef SONG_HPP
#define SONG_HPP

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "Note.hpp"
#include <fstream>
#include "json.hpp" // 第三方 json 解析库

class Song {
public:
    Song(std::string title, std::string artist, int bpm, const std::vector<Note>& notes, int endTime)
        : title(std::move(title)), artist(std::move(artist)), bpm(bpm), notes(notes) ,endTime(endTime){}

    Song(std::ifstream &file) {
        nlohmann::json j;
        file >> j;
        artist = j["artist"];
        bpm = j["bpm"];
        title = j["title"];
        endTime = j["endTime"];
        for (auto& note : j["notes"]) {
            notes.emplace_back(note["timestamp"].get<int>()-320, note["key"], note["type"] == "Tap" ? Note::Tap : Note::Hold);
        }

    }

    const std::string& getTitle() const { return title; }
    const std::string& getArtist() const { return artist; }
    int getBpm() const { return bpm; }
    const std::vector<Note>& getNotes() const { return notes; }
    int getEndTime() const { return endTime; }
    void ShowSong() {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Artist: " << artist << std::endl;
        std::cout << "BPM: " << bpm << std::endl;
        std::cout << "Notes: " << std::endl;
        for (const auto& note : notes) {
            std::cout << "Timestamp: " << note.getTimestamp() << " Track: " << note.getTrack() << " Type: " << (note.getType() == Note::Tap ? "Tap" : "Hold") << std::endl;
        }
    }

private:
    std::string title;
    std::string artist;
    int bpm;
    std::vector<Note> notes;
    int endTime;
};

#endif //SONG_H