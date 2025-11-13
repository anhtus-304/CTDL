#include "time_utils.h"
#include <ctime>

static std::string twoDigit(int v) {
	char buf[3];
	buf[0] = static_cast<char>('0' + (v / 10));
	buf[1] = static_cast<char>('0' + (v % 10));
	buf[2] = '\0';
	return std::string(buf, 2);
}

std::string currentDateISO() {
	std::time_t t = std::time(nullptr);
	std::tm tm{};
#ifdef _WIN32
	localtime_s(&tm, &t);
#else
	tm = *std::localtime(&t);
#endif
	int year = tm.tm_year + 1900;
	int month = tm.tm_mon + 1;
	int day = tm.tm_mday;
	// Chuyển year sang chuỗi thủ công
	char ybuf[16];
	int y = year;
	int idx = 0;
	char rev[16];
	if (y == 0) rev[idx++] = '0';
	while (y > 0 && idx < 15) {
		rev[idx++] = static_cast<char>('0' + (y % 10));
		y /= 10;
	}
	for (int i = 0; i < idx; ++i) ybuf[i] = rev[idx - 1 - i];
	ybuf[idx] = '\0';

	std::string result;
	result.reserve(10);
	result.append(ybuf);
	result.push_back('-');
	result.append(twoDigit(month));
	result.push_back('-');
	result.append(twoDigit(day));
	return result;
}
