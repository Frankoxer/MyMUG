#ifndef KEY_HPP
#define KEY_HPP

#include <chrono>

class Key {
private:
    char content;
    bool isPressed;
	std::chrono::time_point<std::chrono::steady_clock> gameStartTime;
	int pressTimeStamp;
	int releaseTimeStamp;

public:
    // 构造函数
    Key(char c,bool a=false,std::chrono::time_point<std::chrono::steady_clock> t=std::chrono::steady_clock::now(),int t1=0,int t2=0) :
    content(c), isPressed(a), gameStartTime(t),pressTimeStamp(t1),releaseTimeStamp(t2) {}

    // 获取 content 的值
    char getContent() const { return content; }

    // 获取 isPressed 的值
    bool getIsPressed() const { return isPressed; }

	// 获取 pressTimeStamp
	int getPressTimeStamp() const { return pressTimeStamp; }

    // 获取 releaseTimeStamp
	int getReleaseTimeStamp() const { return releaseTimeStamp; }


    // 更新按键状态并设置时间戳
    void updateState(bool pressed) {
        std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
        if (pressed != isPressed) {
            isPressed = pressed;
            if (isPressed) {
                pressTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
            } else {
                releaseTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - gameStartTime).count();
            }
        }
    }
};

#endif //KEY_HPP