#include "Enermy.h"
#include <chrono>
using namespace std::chrono;

Enermy::Enermy(int startX, int startY, int hp, int dmg, int speed)
    : Shared(startX, startY, hp, dmg),
    moveInterval(speed) {           // Khoảng thời gian giữa các lần di chuyển của Enermy
    lastMoveTime = steady_clock::now(); // Lưu thời điểm di chuyển cuối cùng
}

// Hàm di chuyển Enermy
void Enermy::move(int boardWidth, int boardHeight, const std::vector<Bullet>& bullets) {
    auto currentTime = steady_clock::now();                                // Lấy thời điểm hiện tại
    auto elapsedTime = duration_cast<milliseconds>(currentTime - lastMoveTime).count(); // Tính thời gian đã trôi qua kể từ lần di chuyển cuối cùng

    if (elapsedTime >= moveInterval) { // Nếu đủ thời gian di chuyển
        int direction = rand() % 4; // Chọn hướng di chuyển ngẫu nhiên (0: lên, 1: xuống, 2: trái, 3: phải)

        bool isBulletNear = false;
        for (const auto& bullet : bullets) { // Kiểm tra xem có đạn gần Enermy không
            if (bullet.y > y && abs(bullet.x - x) <= 1) {
                isBulletNear = true;
                break;
            }
        }

        if (isBulletNear && rand() % 10 < 9) { // Nếu có đạn gần, 90% khả năng Enermy sẽ né tránh
            if (x > 0) {
                x--; // Né sang trái nếu có thể
            }
            else if (x < boardWidth - 1) {
                x++; // Né sang phải nếu có thể
            }
        }
        else { // Nếu không có đạn gần, di chuyển ngẫu nhiên
            switch (direction) {
            case 0: // Di chuyển lên trên
                if (y > 0) y--;
                break;
            case 1: // Di chuyển xuống dưới
                if (y < boardHeight - 1) y++;
                break;
            case 2: // Di chuyển sang trái
                if (x > 0) x--;
                break;
            case 3: // Di chuyển sang phải
                if (x < boardWidth - 1) x++;
                break;
            }
        }

        lastMoveTime = currentTime; // Cập nhật thời điểm di chuyển cuối cùng
    }
}