 #ifndef READER_H
 #define READER_H

 #include <string>
 using namespace std;

 struct Reader {
	 string id;           // Mã bạn đọc (duy nhất)
	 string fullName;     // Họ tên
	 string registeredAt; // Ngày đăng ký tham gia (YYYY-MM-DD)
 };

 #endif
