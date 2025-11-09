#include "file_utils.h"
#include <fstream>
#include <iostream>
using namespace std;

vector<string> readFileLines(const string &path) {
    vector<string> lines;
    ifstream file(path);
    if (!file) return lines;
    string line;
    while (getline(file, line))
        lines.push_back(line);
    file.close();
    return lines;
}

void writeFileLines(const string &path, const vector<string> &lines, bool append) {
    ofstream file(path, append ? ios::app : ios::out);
    for (auto &line : lines)
        file << line << '\n';
    file.close();
}
