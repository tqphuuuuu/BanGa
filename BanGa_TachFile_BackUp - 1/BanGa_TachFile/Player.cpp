#include "Player.h"

Player::Player(int StartX, int StartY, int hp)
    : Shared(StartX, StartY, hp, 1),
    isUpgraded(false),              // Biến nâng cấp 
    Ammo(false) {}                 // Biến có đạn đặc biệt

// Di chuyển người chơi sang trái
void Player::moveLeft() {
    if (x > 0) x--;
}

// Di chuyển sang phải
void Player::moveRight(int boardWidth) {
    if (x < boardWidth - 1) x++;
}

// Di chuyển người chơi lên trên
void Player::moveUp() {
    if (y > 0) y--;
}

// Di chuyển  xuống dưới
void Player::move_Down(int boardHeight) {
    if (y < boardHeight - 1) y++;
}

// Hàm bắn đạn
void Player::shoot(std::vector<Bullet>& bullets) {
    int bulletSpeed, bulletDamage, bulletColor;

    if (isUpgraded) { // Nếu được nâng cấp
        bulletSpeed = 100;      // Tốc độ đạn nhanh hơn
        bulletDamage = damage * 2; // Sát thương đạn gấp đôi
        bulletColor = 10;         // Màu của đạn
        bullets.emplace_back(x, y, bulletDamage, bulletSpeed, bulletColor); // Thêm một viên đạn vào danh sách
    }
    else if (Ammo) { // Nếu có đạn đặc biệt
        bulletSpeed = 50;       // Tốc độ đạn chậm hơn
        bulletDamage = damage * 5; // Sát thương đạn gấp 5 lần
        bulletColor = 12;        // Màu của đạn 
        // Thêm 5 viên đạn vào danh sách, bắn theo nhiều hướng
        bullets.emplace_back(x, y, bulletDamage, bulletSpeed, bulletColor);
        bullets.emplace_back(x - 1, y - 1, bulletDamage, bulletSpeed, bulletColor);
        bullets.emplace_back(x + 1, y - 1, bulletDamage, bulletSpeed, bulletColor);
        bullets.emplace_back(x - 1, y, bulletDamage, bulletSpeed, bulletColor);
        bullets.emplace_back(x + 1, y, bulletDamage, bulletSpeed, bulletColor);
    }
    else { // Trường hợp bình thường
        bulletSpeed = 100;
        bulletDamage = damage;
        bulletColor = 14;
        bullets.emplace_back(x, y, bulletDamage, bulletSpeed, bulletColor); // Thêm một viên đạn vào danh sách
    }
}

// Nâng cấp người chơi
void Player::upgrade() {
    isUpgraded = true;
    resetAmmo(); // Đảm bảo không có đạn đặc biệt khi được nâng cấp
}

// Sử dụng đạn đặc biệt
void Player::ammo() {
    Ammo = true;
    resetUpgrade(); // Đảm bảo không được nâng cấp khi sử dụng đạn đặc biệt
}

// Thiết lập trạng thái đạn đặc biệt
void Player::setAmmo(bool value) {
    Ammo = value;
}

// Kiểm tra xem người chơi có được nâng cấp hay không
bool Player::getIsUpgraded() {
    return isUpgraded;
}

// Hủy nâng cấp
void Player::resetUpgrade() {
    isUpgraded = false;
}

// Hủy đạn đặc biệt
void Player::resetAmmo() {
    Ammo = false;
}