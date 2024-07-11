//
// Created by Frankoxer on 24-7-11.
//

#ifndef MUSICTHREAD_H
#define MUSICTHREAD_H

#include <QThread>
#include <windows.h>

class MusicThread : public QThread {
    Q_OBJECT
public:
    explicit MusicThread(LPCSTR songPathChar) : songPathChar(songPathChar) {}

protected:
    void run() override;

private:
    LPCSTR songPathChar;
};



#endif //MUSICTHREAD_H
