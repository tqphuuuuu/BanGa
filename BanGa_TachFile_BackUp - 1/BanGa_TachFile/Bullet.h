#ifndef BULLET_H
#define BULLET_H

#include "Shared.h"
#include <chrono>

using namespace std::chrono;

class Bullet : public Shared {
private:
    steady_clock::time_point lastMoveTime;
    int moveInterval;
    int color;


public:
    Bullet(int x, int y, int dmg, int interval, int bulletColor = 14);
    void move();
    bool isOutOfScreen(int screenHeight);


    int getColor() const;

    void setColor(int newColor);
};

#endif // BULLET_H
