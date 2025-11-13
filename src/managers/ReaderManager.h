 #ifndef READERMANAGER_H
 #define READERMANAGER_H

 #include <string>
 #include <vector>
 #include <unordered_set>
 #include <unordered_map>
 #include "../models/Reader.h"

 class ReaderManager {
 private:
	 std::string dataFile = "data/Reader.txt";

	 // Cache và chỉ mục để tránh đọc file nhiều lần
	 bool loaded = false;
	 std::vector<Reader> readers;
	 std::unordered_set<std::string> idSet;
	 std::unordered_multimap<std::string, size_t> nameIndex; // key: tên chuẩn hóa, value: index trong readers

	 void ensureLoaded();
	 static std::string normalizeName(const std::string &s);

 public:
	 // Đọc toàn bộ bạn đọc (đồng thời nạp cache nếu chưa nạp)
	 std::vector<Reader> loadReaders();

	 // Thêm bạn đọc mới: tạo mã duy nhất, gán ngày đăng ký, lưu file
	 Reader addReader(const std::string &fullName);

	 // Tìm kiếm theo tên (khớp chính xác theo normalizeName)
	 std::vector<Reader> findByName(const std::string &name);

	 // Tiện ích: liệt kê nhanh
	 void printReaders();
 };

 #endif
