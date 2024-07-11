//
// Created by Frankoxer on 24-7-11.
//

#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H

#include <QThread>
#include <utility>
#include <windows.h>

class MusicThread : public QThread {
    Q_OBJECT
public:
    explicit MusicThread() {}
    void setPath(std::string songPathChar) { this->songPathChar = std::move(songPathChar); }

protected:
    void run() override;

private:
    std::string songPathChar;
};



#endif //MUSICTHREAD_H
