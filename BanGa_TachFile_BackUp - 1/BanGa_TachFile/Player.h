#ifndef PLAYER_H
#define PLAYER_H

#include "Shared.h"
#include "Bullet.h"
#include <vector>

class Player : public Shared {
private:
    bool isUpgraded;
    bool Ammo;

public:
    Player(int startX, int startY, int hp);
    void moveLeft();

    void moveRight(int boardWidth);

    void moveUp();

    void move_Down(int boardHeight);

    void shoot(std::vector<Bullet>& bullets);

    void upgrade();

    void ammo();

    void setAmmo(bool value);

    bool getIsUpgraded();

    void resetUpgrade();

    void resetAmmo();
};

#endif // PLAYER_H
