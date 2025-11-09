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

public:
    bool loadAdmins();
    bool login();
};

#endif
