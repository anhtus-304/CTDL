#include "MainMenu.h"
#include "../managers/AuthManager.h"
#include "../utils/color_utils.h"
#include <iostream>
using namespace std;

void MainMenu::show() {
    AuthManager auth;
    if (!auth.login()) return;  // Nếu đăng nhập sai 3 lần thì thoát

    int choice;
    do {
        setColor(11);
        cout << "\n======= MENU CHÍNH =======\n";
        resetColor();
        cout << "1. Quản lý sách\n";
        cout << "2. Quản lý bạn đọc\n";
        cout << "3. Quản lý phiếu mượn\n";
        cout << "0. Thoát\n";
        cout << "===========================\n";
        cout << "Nhập lựa chọn: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "[TBD] Gọi menu Sach ở đây...\n";
                break;
            case 2:
                cout << "[TBD] Gọi menu BanDoc ở đây...\n";
                break;
            case 3:
                cout << "[TBD] Gọi menu PhieuMuon ở đây...\n";
                break;
            case 0:
                cout << "👋 Thoát chương trình.\n";
                break;
            default:
                cout << "❌ Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 0);
}
