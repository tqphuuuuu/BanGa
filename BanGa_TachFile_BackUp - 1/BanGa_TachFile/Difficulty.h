#ifndef DIFFICULTY_H
#define DIFFICULTY_H

class Difficulty {
public:
    int initialHealth;     // máu khởi đầu
    int number_Chicken;    // Số lượng kẻ thù
    int hp_Chicken;        // máu của kẻ thù
    int dmg_Chicken;       // Sát thương của kẻ thù
    int speed_Chicken;     // Tốc độ di chuyển của kẻ thù

    // Constructor với các tham số đầu vào
    Difficulty(int health, int numChicken, int hp, int dmg, int speed);

    // Constructor mặc định
    Difficulty();
};

#endif // DIFFICULTY_H
