#include "Board.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace chrono;

Board::Board(int w, int h, int hp, int numberEnermy, int hp_chicken, int dmg_chicken, int sp_Chicken)
    : width(w), height(h), player(w / 2, h - 1, hp), frameCount(0), fps(0), lastFPS(0), numberenemies(numberEnermy),
    health_Chicken(hp_chicken), dmg_Chicken(dmg_chicken), speed_Chicken(sp_Chicken) {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Board::clearScreen() {
    system("cls");
}

void Board::setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void Board::setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}


void Board::SpawnChicken() {
    if (!hasEnemyOnBoard()) {
        for (int i = 0; i < numberenemies; ++i) {
            int spawnX = rand() % width; // Vị trí xuất hiện ngẫu nhiên của kẻ thù
            enemies.emplace_back(spawnX, 0, health_Chicken, dmg_Chicken, speed_Chicken);
        }
    }
}
void Board::respawnChickens() {
    if (!bossActive && !hasEnemyOnBoard()) {
        SpawnChicken();
        chickenTurnsCleared++; // Tăng số turn gà đã bị tiêu diệt
    }
}

void Board::spawnBoss() {
    if (!bossActive && chickenTurnsCleared >= 3) { // Kiểm tra số turn gà đã bị tiêu diệt
        boss = new Boss(width / 2, 0, 10, 10, 100);
        bossActive = true;
        enemies.clear(); // Xóa tất cả gà khi Boss xuất hiện
        chickenTurnsCleared = 0; // Reset số turn gà đã bị tiêu diệt
    }
}

void Board::input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a') {
            player.moveLeft();
           
        }
        else if (key == 'd') {
            player.moveRight(width);
        }
        else if (key == 'w') {
            player.moveUp();
        }
        else if (key == 's') {
            player.move_Down(height);
        }

        else if (key == '1') {
            player.upgrade(); // Nâng cấp vũ khí khi nhấn phím 1
        }
        else if (key == '0') {
            player.resetUpgrade();// Khôi phục cài đặt gốc
            player.resetAmmo();
        }
        else if (key == '2') {
            player.ammo(); // Bắn nhiều đạn khi bấm phím 2
        }
        else if (key == ' ') {
            PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\shoot.wav"), NULL, SND_FILENAME | SND_ASYNC);
            player.shoot(bullets);
           
        }
    }
}

bool Board::hasEnemyOnBoard() {
    return !enemies.empty(); // Kiểm tra xem có kẻ thù trên bảng trò chơi không
}

void Board::upDate() {
    // Di chuyển đạn
    for (auto& bullet : bullets) {
        bullet.move();
    }

    // Di chuyển kẻ thù
    for (auto& chicken : enemies) {
        chicken.move(width, height, bullets);
    }

    // Di chuyển Boss nếu nó đang hoạt động
    if (bossActive) {
        boss->move(width, height, bullets);

        // Kiểm tra va chạm giữa Boss và người chơi 
        if (boss->x == player.x && boss->y == player.y) {
            player.takeDamage(boss->damage);
        }
    }

    // Kiểm tra va chạm giữa kẻ thù và người chơi
    for (auto& chicken : enemies) {
        if (chicken.x == player.x && chicken.y == player.y) {
            player.takeDamage(chicken.damage);
        }
    }

    // Xử lý va chạm giữa đạn và kẻ thù
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletHit = false;

        // Kiểm tra va chạm giữa đạn và kẻ thù
        for (auto chickenIt = enemies.begin(); chickenIt != enemies.end();) {
            if (bulletIt->x == chickenIt->x && bulletIt->y == chickenIt->y) {
                chickenIt->takeDamage(bulletIt->damage);
                bulletHit = true;

                if (chickenIt->isDead()) {
                    point++;
                    chickenIt = enemies.erase(chickenIt); // Xóa kẻ thù bị tiêu diệt
                }
                else {
                    ++chickenIt;
                }
            }
            else {
                ++chickenIt;
            }
        }

        // Kiểm tra va chạm giữa đạn và Boss
        if (bossActive && bulletIt->x == boss->x && bulletIt->y == boss->y) {
            boss->takeDamage(bulletIt->damage);
            bulletHit = true;

            if (boss->isDead()) {
                point += 15; // Điểm  khi tiêu diệt Boss
                delete boss; // Giải phóng bộ nhớ cho Boss
                boss = nullptr; // Đặt boss thành nullptr để tránh lỗi con trỏ hoang
                bossActive = false; // Đặt bossActive thành false
                respawnChickens(); // Xuất hiện gà mới sau khi Boss bị tiêu diệt
            }
        }
        else {
            spawnBoss(); // Sinh Boss nếu đủ điểm và không có Boss
            respawnChickens(); // Sinh gà nếu không có Boss và không còn kẻ thù
        }

        // Xóa đạn nếu đã trúng hoặc ra ngoài màn hình
        if (bulletHit || bulletIt->isOutOfScreen(height)) {
            bulletIt = bullets.erase(bulletIt);
        }
        else {
            ++bulletIt;
        }
    }

    if (player.isDead()) {
        cout << "Game Overrrr";
        exit(0); // Kết thúc trò chơi khi người chơi chết
    }
    if (bossActive) {
        if (boss->isDead()) {
            delete boss; // Xóa Boss khi Boss bị tiêu diệt
            boss = nullptr;
            bossActive = false;
            SpawnChicken(); // Sinh lại gà
        }
    }
    else {
        spawnBoss(); // Sinh Boss nếu không có Boss và không còn kẻ thù
    }

}

void Board:: displayFPS() {
    setCursorPosition(width + 20, 0); // Đặt con trỏ ở vị trí cần hiển thị FPS
    setColor(7);
    cout << "FPS: " << fps; // In FPS 

    setCursorPosition(width + 20, 1); // Đặt con trỏ ở vị trí cần hiển thị máu
    setColor(7);
    cout << "Health: " << player.health << endl; // Hiển thị máu của người chơi
    setCursorPosition(width + 20, 2); // Đặt con trỏ ở vị trí cần hiển thị điểm
    setColor(7);
    cout << "Points: " << point << endl; // Hiển thị điểm số
    setCursorPosition(0, height + 2); // Đặt con trỏ ở vị trí cần hiển thị điểm


}

void Board::render() {
    auto startRenderTime = steady_clock::now(); // Thời điểm bắt đầu render
    clearScreen(); // Xóa màn hình console

    setColor(11); // Set màu cyan cho bảng
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    for (int i = 0; i < width + 2; i++) cout << char(219) << char(219);
    cout << endl;

    for (int y = 0; y < height; ++y) {
        cout << char(219);
        for (int x = 0; x < width; ++x) {
            bool drawn = false;

            if (bossActive && boss) {
                if (boss->x == x && boss->y == y) {
                    setColor(13); // Đặt màu cho boss
                    cout << char(254); // Vẽ boss
                    setColor(11); // Đặt lại màu cho bảng
                    drawn = true;
                }
            }

            if (!drawn) {
                for (const auto& chicken : enemies) {
                    if (chicken.x == x && chicken.y == y) {
                        setColor(12); // Đặt màu cho gà
                        cout << char(233); // Vẽ gà
                        setColor(11); // Đặt lại màu cho bảng
                        drawn = true;
                        break;
                    }
                }
            }

            if (!drawn) {
                for (const auto& bullet : bullets) {
                    if (bullet.x == x && bullet.y == y) {
                        setColor(bullet.getColor()); // Lấy màu từ đối tượng đạn
                        cout << char(248);
                        setColor(11);
                        drawn = true;
                        break;
                    }
                }
            }


            if (!drawn) {
                if (player.x == x && player.y == y) {
                    setColor(10); // Đặt màu cho người chơi
                    cout << char(207); // Vẽ người chơi
                    setColor(11); // Đặt lại màu cho bảng
                    drawn = true;
                }
            }

            if (!drawn) {
                cout << ' '; // Vẽ khoảng trống
            }
            cout << " "; // Thêm khoảng trống giữa các ô
        }
        cout << "  " << char(219) << endl;
        cout << endl; // Thêm dòng trống giữa các dòng
    }

    for (int i = 0; i < width + 2; i++) cout << char(219) << char(219);
    cout << endl;
    displayFPS(); // Hiển thị FPS và thông tin khác
    auto endRenderTime = steady_clock::now(); // Thời điểm kết thúc render
    auto renderTime = duration_cast<milliseconds>(endRenderTime - startRenderTime).count(); // Thời gian đã trôi qua trong quá trình render
    if (renderTime < 1000 / 60) {
        this_thread::sleep_for(milliseconds(1000 / 60 - renderTime)); // Ngủ đủ thời gian để duy trì 60 FPS

    }
    fps = 800 / static_cast<double>(renderTime); // Tính FPS hiện tại




}

void Board::run() {
    lastFrameTime = steady_clock::now();
    //PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\Nen.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\Nen.wav")) {
    }

    // Phát nhạc nền (chạy lặp lại)
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
    while (player.health > 0) {
        input();
        upDate();
        render();/*
        frameCount++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));*/
    }
     // Dừng nhạc nền khi game kết thúc
    PlaySound(NULL, 0, 0); 

    cout << "Game Over! Your score: " << point << endl;
}

