#ifndef BOSS_H
#define BOSS_H

#include "Enermy.h"
#include "Bullet.h"
#include <vector>

class Boss : public Enermy {
public:
    Boss(int StartX, int StartY, int hp, int dmg, int speed);

    void move(int boardWidth, int boardHeight, const std::vector<Bullet>& bullets) override; // Ghi đè phương thức move của Enermy
};

#endif // BOSS_H
