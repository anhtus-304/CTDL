#include "string_utils.h"
#include <sstream>
#include <algorithm>
#include <cctype>

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == string::npos || end == string::npos) return "";
    return s.substr(start, end - start + 1);
}

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delimiter))
        tokens.push_back(token);
    return tokens;
}
