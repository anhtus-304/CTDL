#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "../models/Admin.h"
#include <vector>
#include <string>
using namespace std;

class AuthManager {
private:
    vector<Admin> admins;
    string dataFile = "data/Admin.txt";

    bool usernameExists(const string &u);

public:
    bool loadAdmins();
    bool login();
    bool registerUser(); // Đăng ký tài khoản mới (user, password, xác nhận)
};

#endif
