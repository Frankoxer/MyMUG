#ifndef NOTE_HPP
#define NOTE_HPP

class Note {
public:
    enum Type {
        Tap,
        Hold
    };

    Note (int ts, int tr, Type ty) : timestamp(ts), track(tr), type(ty) {}

    Type getType() const { return type; }

    int getTimestamp() const { return timestamp; }

    int getTrack() const { return track; }

public:
    int timestamp;
    int track;
    Type type;
};

#endif //NOTE_H