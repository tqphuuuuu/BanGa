#include "Bullet.h"
#include <chrono>

// Constructor của Bullet
Bullet::Bullet(int x, int y, int dmg, int interval, int bulletColor)
    : Shared(x, y, 0, dmg), 
    moveInterval(interval), // Khoảng thời gian giữa các lần di chuyển của đạn
    color(bulletColor) {   // Màu sắc của đạn
    lastMoveTime = steady_clock::now(); // Lưu thời điểm di chuyển cuối cùng
}

// Hàm di chuyển đạn
void Bullet::move() {
    auto currentTime = steady_clock::now(); // Lấy thời điểm hiện tại
    auto elapsedTime = duration_cast<milliseconds>(currentTime - lastMoveTime).count(); // Tính thời gian đã trôi qua kể từ lần di chuyển cuối cùng

    if (elapsedTime >= moveInterval) { // Nếu đủ thời gian di chuyển
        y--; // Di chuyển đạn lên trên 1 đơn vị
        lastMoveTime = currentTime; // Cập nhật thời điểm di chuyển cuối cùng
    }
}

// Kiểm tra xem đạn đã ra khỏi màn hình hay chưa
bool Bullet::isOutOfScreen(int screenHeight) {
    return y < 0; // Đạn ra khỏi màn hình khi tọa độ y nhỏ hơn 0
}

// Lấy màu sắc của đạn
int Bullet::getColor() const {
    return color;
}

// Thiết lập màu sắc mới cho đạn
void Bullet::setColor(int newColor) {
    color = newColor;
}