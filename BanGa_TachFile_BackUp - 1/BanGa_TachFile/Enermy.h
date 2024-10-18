#ifndef ENERMY_H
#define ENERMY_H

#include "Shared.h"
#include "bullet.h"
#include <chrono>
#include <vector>
using namespace std::chrono;

class Enermy : public Shared {
private:
    std::chrono::steady_clock::time_point lastMoveTime;
    int moveInterval;

public:
    Enermy(int StartX, int StartY, int hp, int dmg, int speed);

    virtual  void move(int boardWidth, int boardHeight, const std::vector<Bullet>& bullets);
};

#endif // ENERMY_H