#include "ReaderManager.h"
#include "../utils/file_utils.h"
#include "../utils/time_utils.h"
#include "../utils/color_utils.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cctype>

using namespace std;

// Chuyển số dương sang chuỗi không dùng to_string/stringstream
static string intToString(int num) {
	if (num == 0) return "0";
	char buf[32];
	int idx = 0;
	while (num > 0 && idx < 31) {
		int digit = num % 10;
		buf[idx++] = static_cast<char>('0' + digit);
		num /= 10;
	}
	string s;
	s.reserve(idx);
	for (int i = idx - 1; i >= 0; --i) s.push_back(buf[i]);
	return s;
}

// Tạo ID dạng R + 5 chữ số, không dùng iomanip
static string makeIdFromNumber(int num) {
	string digits = intToString(num);
	// pad với '0' về độ dài 5
	string padded;
	if (digits.length() < 5) padded.assign(5 - digits.length(), '0');
	padded += digits;
	return string("R") + padded;
}

// Parse số dương từ chuỗi (bỏ qua ký tự không phải số)
static int parsePositiveInt(const string &s) {
	long long val = 0;
	for (char ch : s) {
		if (ch >= '0' && ch <= '9') {
			val = val * 10 + (ch - '0');
			if (val > 2147483647LL) return 2147483647; // clamp
		}
	}
	return static_cast<int>(val);
}

// Tách 3 cột CSV đơn giản (id, name, date) không dùng split
static void csvSplit3(const string &line, string &a, string &b, string &c) {
	a.clear(); b.clear(); c.clear();
	int field = 0;
	for (size_t i = 0; i < line.size(); ++i) {
		char ch = line[i];
		if (ch == ',') {
			++field;
			if (field > 2) { // phần dư bỏ vào c
				c.push_back(ch);
			}
			continue;
		}
		if (field == 0) a.push_back(ch);
		else if (field == 1) b.push_back(ch);
		else c.push_back(ch);
	}
}

// Trim thủ công trái/phải
static string localTrim(const string &s) {
	size_t start = 0, end = s.size();
	while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
	return s.substr(start, end - start);
}

// Chuẩn hóa tên: trim + tolower (thủ công, không dùng transform)
string ReaderManager::normalizeName(const string &s) {
	// Trim trái/phải
	size_t start = 0, end = s.size();
	while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
	string out;
	out.reserve(end - start);
	for (size_t i = start; i < end; ++i) out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(s[i]))));
	return out;
}

void ReaderManager::ensureLoaded() {
	if (loaded) return;
	readers.clear();
	idSet.clear();
	nameIndex.clear();
	auto lines = readFileLines(dataFile);
	if (!lines.empty()) readers.reserve(lines.size());
	for (auto &line : lines) {
		if (localTrim(line).empty()) continue;
		string a, b, c;
		csvSplit3(line, a, b, c);
		if (!a.empty() || !b.empty() || !c.empty()) {
			Reader r{ localTrim(a), localTrim(b), localTrim(c) };
			readers.push_back(r);
			idSet.insert(r.id);
			nameIndex.emplace(normalizeName(r.fullName), readers.size() - 1);
		}
	}
	loaded = true;
}

vector<Reader> ReaderManager::loadReaders() {
	ensureLoaded();
	return readers; // copy nhẹ; số lượng nhỏ trong console app
}

 Reader ReaderManager::addReader(const std::string &fullName) {
	 // Lấy số thứ tự lớn nhất hiện có
	ensureLoaded();
	int maxNum = 0;
	for (auto &r : readers) {
		 if (!r.id.empty() && r.id[0] == 'R') {
			int n = parsePositiveInt(r.id.substr(1));
			if (n > maxNum) maxNum = n;
		 }
	 }
	 int next = maxNum + 1;
	// Đảm bảo mã sinh ra chưa tồn tại nếu file bị chỉnh tay
	while (idSet.find(makeIdFromNumber(next)) != idSet.end()) ++next;
	 Reader r;
	 r.id = makeIdFromNumber(next);
	 r.fullName = fullName;
	 r.registeredAt = currentDateISO();

	vector<string> line{ r.id + "," + r.fullName + "," + r.registeredAt };
	 writeFileLines(dataFile, line, /*append*/ true);

	 setColor(10);
	 cout << "✅ Đã thêm bạn đọc: " << r.fullName << " (" << r.id << ")\n";
	 resetColor();
	// Cập nhật cache và chỉ mục
	readers.push_back(r);
	idSet.insert(r.id);
	nameIndex.emplace(normalizeName(r.fullName), readers.size() - 1);
	return r;
 }

 void ReaderManager::printReaders() {
	ensureLoaded();
	const auto &list = readers;
	 if (list.empty()) {
		 cout << "(Chưa có bạn đọc nào)\n";
		 return;
	 }
	 setColor(11);
	 cout << "\n--- DANH SÁCH BẠN ĐỌC ---\n";
	 resetColor();
	 for (auto &r : list) {
		 cout << r.id << " | " << r.fullName << " | đăng ký: " << r.registeredAt << "\n";
	 }
 }

vector<Reader> ReaderManager::findByName(const std::string &name) {
	ensureLoaded();
	vector<Reader> result;
	string key = normalizeName(name);
	auto range = nameIndex.equal_range(key);
	for (auto it = range.first; it != range.second; ++it) {
		size_t idx = it->second;
		if (idx < readers.size()) result.push_back(readers[idx]);
	}
	return result;
}
