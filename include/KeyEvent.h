#ifndef MYMUG_KEYEVENT_H
#define MYMUG_KEYEVENT_H

#include <QString>

class KeyEvent {
public:
    KeyEvent(int key, const QString &keyText) : key(key), keyText(keyText) {}

    int getKey() const { return key; }
    const QString &getKeyText() const { return keyText; }
    qint64 getPressTime() const { return pressTime; }
    qint64 getReleaseTime() const { return releaseTime; }

    void setPressTime(qint64 time) { pressTime = time; }
    void setReleaseTime(qint64 time) { releaseTime = time; }

private:
    int key;
    QString keyText;
    qint64 pressTime;
    qint64 releaseTime;
};

#endif // MYMUG_KEYEVENT_H
