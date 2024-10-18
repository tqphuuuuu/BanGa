#include "Difficulty.h"

// Constructor với các tham số đầu vào
Difficulty::Difficulty(int health, int numChicken, int hp, int dmg, int speed)
    : initialHealth(health), number_Chicken(numChicken), hp_Chicken(hp), dmg_Chicken(dmg), speed_Chicken(speed) {}

// Constructor mặc định
Difficulty::Difficulty()
    : initialHealth(0), number_Chicken(0), hp_Chicken(0), dmg_Chicken(0), speed_Chicken(0) {}
