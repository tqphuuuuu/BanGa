#ifndef SHARED_H
#define SHARED_H

class Shared {
public:
    int x, y;
    int health;
    int damage;

    Shared(int startX, int startY, int hp, int dmg);
    void takeDamage(int dmg);
    bool isDead() const;
};

#endif // SHARED_H
