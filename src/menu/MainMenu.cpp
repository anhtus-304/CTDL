#include "MainMenu.h"
#include "BookMenu.h"
#include "AuthMenu.h"
#include "ReaderMenu.h"
#include "../utils/color_utils.h"
#include <iostream>
using namespace std;

void MainMenu::show() {
    AuthMenu authMenu;
    if (!authMenu.show()) return; // Thoát nếu người dùng không đăng nhập

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
                BookMenu bookMenu;
                bookMenu.show();
                break;
            case 2: {
                ReaderMenu rm;
                rm.show();
                break;
            }
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
