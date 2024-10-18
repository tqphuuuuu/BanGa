#include <iostream>
#include "Menu.h"

using namespace std;

void displayMainMenu() {
    cout << "===== MENU =====" << endl;
    cout << "0. Thoat" << endl;
    cout << "1. Play Game" << endl;
    cout << "2. Lua chon do kho" << endl;
    cout << "================" << endl;
    cout << "Nhap lua chon cua ban: ";
}

int chooseDifficulty() {
    int difficulty;
    cout << "Chon do kho (1: De, 2: Trung Binh, 3: Kho): ";
    cin >> difficulty;

    switch (difficulty) {
    case 1:
        
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    default:
        cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        return chooseDifficulty();
    }
}
