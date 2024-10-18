#include "Boss.h"

Boss::Boss(int StartX, int StartY, int hp, int dmg, int speed)
    : Enermy(StartX, StartY, hp, dmg, speed) {
    // Boss có thể có thuộc tính hoặc hành vi khác nếu cần
}

void Boss::move(int boardWidth, int boardHeight, const std::vector<Bullet>& bullets) {
    Enermy::move(boardWidth, boardHeight, bullets); // Gọi phương thức move của lớp cơ sở
}
