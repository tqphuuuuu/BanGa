#include "Board.h"
#include "Menu.h"
#include "Difficulty.h"
int main() {
    int choice;
    int difficulty = 2; // Độ khó mặc định là 2 (Trung Bình)

    displayMainMenu(); // Hiển thị menu chính
    cin >> choice;

    switch (choice) {
    case 0:
        cout << "Thoat game" << endl;
        return 0;
    case 1:
        break; // Bắt đầu trò chơi
    case 2:
        PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\StartGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
        difficulty = chooseDifficulty(); // Lựa chọn độ khó
        break;
    default:
        cout << "Lua chon khong hop le. Thoat." << endl;
        return main(); // Lựa chọn không hợp lệ, yêu cầu chọn lại
    }

    // Tạo các  chế độ cho từng mức độ khó
    Difficulty easy(150, 10, 1, 1, 300);
    Difficulty medium(100, 15, 2, 1, 200);
    Difficulty hard(75, 20, 6, 3, 90);

    Difficulty config;

    switch (difficulty) {
    case 1:
        PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\Choose.wav"), NULL, SND_FILENAME | SND_ASYNC);
        config = easy; // Chọn chế độ dễ
        break;
    case 2:
        PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\Choose.wav"), NULL, SND_FILENAME | SND_ASYNC);

        config = medium; // Chọn chế độ trung bình
        break;
    case 3:
        PlaySound(TEXT("C:\\Users\\OS\\Desktop\\C\\BanGa_TachFile\\Choose.wav"), NULL, SND_FILENAME | SND_ASYNC);

        config = hard; // Chọn chế độ khó
        break;
    default:
        cout << "Lua chon do kho khong hop le. Thoat." << endl;
        return 1;
    }

    // Tạo bảng trò chơi với các tham số chế độ
    Board board(15, 10, config.initialHealth, config.number_Chicken, config.hp_Chicken, config.dmg_Chicken, config.speed_Chicken);
    board.run(); // Chạy trò chơi

    return 0;
}
