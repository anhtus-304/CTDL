#include "AuthManager.h"
#include "../utils/file_utils.h"
#include "../utils/color_utils.h"
#include <iostream>
#include <conio.h>  // _getch() để ẩn password khi nhập
#include <cctype>

using namespace std;

// Trim thủ công (thay vì dùng util) để tuân thủ yêu cầu cấu trúc dữ liệu
static std::string localTrim(const std::string &s) {
    size_t start = 0, end = s.size();
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

// Tách 2 trường username,password không dùng split
static bool parseAdminLine(const std::string &line, std::string &u, std::string &p) {
    u.clear(); p.clear();
    bool second = false;
    for (char ch : line) {
        if (ch == ',') {
            if (second) { // thêm dấu phẩy thừa -> coi như lỗi
                return false;
            }
            second = true;
            continue;
        }
        if (!second) u.push_back(ch); else p.push_back(ch);
    }
    u = localTrim(u);
    p = localTrim(p);
    return !u.empty() && !p.empty();
}

bool AuthManager::loadAdmins() {
    std::vector<std::string> lines = readFileLines(dataFile);
    if (lines.empty()) return false;

    admins.clear();
    admins.reserve(lines.size());
    std::string u, p;
    for (auto &line : lines) {
        if (parseAdminLine(line, u, p)) {
            Admin a{ u, p };
            admins.push_back(a);
        }
    }
    return !admins.empty();
}

bool AuthManager::usernameExists(const string &u) {
    for (auto &a : admins) if (a.username == u) return true;
    return false;
}

static string readMasked(const string &prompt) {
    cout << prompt;
    string password;
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
    cout << '\n';
    return password;
}

bool AuthManager::registerUser() {
    // Đảm bảo danh sách đã nạp
    loadAdmins();
    string username;
    cout << "Nhập username mới: ";
    getline(cin, username);
    username = localTrim(username);
    if (username.empty()) {
        setColor(12); cout << "❌ Username không được rỗng\n"; resetColor();
        return false;
    }
    // Không chứa dấu phẩy để tránh hỏng CSV
    for (char ch : username) {
        if (ch == ',') { setColor(12); cout << "❌ Username không được chứa dấu phẩy\n"; resetColor(); return false; }
    }
    if (usernameExists(username)) {
        setColor(12); cout << "❌ Username đã tồn tại\n"; resetColor();
        return false;
    }
    string pass1 = readMasked("Nhập mật khẩu: ");
    string pass2 = readMasked("Nhập lại mật khẩu: ");
    if (pass1 != pass2) {
        setColor(12); cout << "❌ Mật khẩu không khớp\n"; resetColor();
        return false;
    }
    if (pass1.empty()) {
        setColor(12); cout << "❌ Mật khẩu không được rỗng\n"; resetColor();
        return false;
    }
    // Ghi vào file
    vector<string> line{ username + "," + pass1 };
    writeFileLines(dataFile, line, true);
    // Cập nhật bộ nhớ
    admins.push_back(Admin{ username, pass1 });
    setColor(10); cout << "✅ Đăng ký thành công! Có thể đăng nhập ngay.\n"; resetColor();
    return true;
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
