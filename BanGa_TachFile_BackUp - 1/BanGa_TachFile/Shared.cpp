#include "Shared.h"

Shared::Shared(int startX, int startY, int hp, int dmg) : x(startX), y(startY), health(hp), damage(dmg) {}

void Shared::takeDamage(int dmg) {
    health -= dmg;
}

bool Shared::isDead() const {
    return health < 0;
}
