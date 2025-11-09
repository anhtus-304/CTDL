#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>
using namespace std;

vector<string> readFileLines(const string &path);
void writeFileLines(const string &path, const vector<string> &lines, bool append = false);

#endif
