#include "AuthManager.h"
#include "../utils/file_utils.h"
#include "../utils/string_utils.h"
#include "../utils/color_utils.h"
#include <iostream>
#include <conio.h>  // _getch() để ẩn password khi nhập

using namespace std;

bool AuthManager::loadAdmins() {
    vector<string> lines = readFileLines(dataFile);
    if (lines.empty()) return false;

    admins.clear();
    for (auto &line : lines) {
        auto parts = split(line, ',');
        if (parts.size() == 2) {
            Admin a{ trim(parts[0]), trim(parts[1]) };
            admins.push_back(a);
        }
    }
    return !admins.empty();
}

bool AuthManager::login() {
    if (!loadAdmins()) {
        setColor(12);
        cout << "❌ Lỗi: Không thể đọc file " << dataFile << "\n";
        resetColor();
        return false;
    }

    string username, password;
    int attempts = 3;

    while (attempts--) {
        setColor(14);
        cout << "\n===== ĐĂNG NHẬP HỆ THỐNG =====\n";
        resetColor();

        cout << "User: ";
        getline(cin, username);

        cout << "Password: ";
        password.clear();
        char ch;
        while ((ch = _getch()) != '\r') { // enter
            if (ch == 8 && !password.empty()) { // backspace
                password.pop_back();
                cout << "\b \b";
            } else if (ch != 8) {
                password.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;

        for (auto &a : admins) {
            if (a.username == username && a.password == password) {
                setColor(10);
                cout << "✅ Đăng nhập thành công!\n";
                resetColor();
                return true;
            }
        }

        setColor(12);
        cout << "❌ Sai tài khoản hoặc mật khẩu. Còn " << attempts << " lần thử.\n";
        resetColor();
    }

    cout << "❌ Quá số lần cho phép. Thoát chương trình.\n";
    return false;
}
