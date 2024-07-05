//#ifndef VIEWMODEL_H
//#define VIEWMODEL_H
//
//#include <QObject>
//#include <vector>
//#include <chrono>
//#include "Song.hpp"
//#include "Key.hpp"
//
//typedef struct {
//    int x;
//    int y;
//} NoteInfo;
//
//class ViewModel : public QObject {
//Q_OBJECT
//
//public:
//    explicit ViewModel(const std::string &songFilePath, QObject *parent = nullptr);
//
//public slots:
//    void updateKeys(const QVector<bool> &keys);
//    void runGame();
//
//private:
//    void processNotes();
//    void checkNoteHit();
//
//    Song song;
//    std::vector<Note>::iterator it;
//    std::vector<NoteInfo> activeNotes;
//    Key keys[4];
//    std::chrono::steady_clock::time_point gameStartTime;
//    int point = 0;
//    static constexpr int LENGTH = 1440;
//    static constexpr int HEIGHT = 900;
//    static constexpr int line = 750;
//    static constexpr int leftestTrack = 480;
//    static constexpr int width = 120;
//    static constexpr int noteHeight = 20;
//    static constexpr int time_interval = 16;
//    static constexpr int speed = 1;
//    static constexpr int perfectTime = 80;
//    bool keyFromView[4] = {false, false, false, false};
//};
//
//#endif // VIEWMODEL_H
