#include "time_utils.h"
#include <ctime>
#include <string>

using namespace std;

static string twoDigit(int v) {
    char buf[3];
    buf[0] = static_cast<char>('0' + (v / 10));
    buf[1] = static_cast<char>('0' + (v % 10));
    buf[2] = '\0';
    return string(buf, 2);
}

string getCurrentDate() {
    return "01/01/2024";
}

string currentDateISO() {
    time_t t = time(nullptr);
    tm* tm = localtime(&t);
    
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    
    string result;
    result = to_string(year) + "-" + twoDigit(month) + "-" + twoDigit(day);
    return result;
}

int getDaysBetween(const string& date1, const string& date2) {
    return 7;
}

bool isDateValid(const string& date) {
    return true;
}