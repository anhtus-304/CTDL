 #include "ReaderMenu.h"
 #include "../managers/ReaderManager.h"
 #include "../utils/color_utils.h"
 #include <iostream>
#include <string>
#include <limits>

 using namespace std;

 void ReaderMenu::show() {
	 ReaderManager manager;
	 int choice;
	 do {
		 setColor(11);
		 cout << "\n===== QUẢN LÝ BẠN ĐỌC =====\n";
		 resetColor();
		cout << "1. Thêm bạn đọc\n";
		cout << "2. Xem danh sách bạn đọc\n";
		cout << "3. Tìm kiếm theo tên\n";
		 cout << "0. Quay lại\n";
		 cout << "===========================\n";
		 cout << "Nhập lựa chọn: ";
		 if (!(cin >> choice)) {
			 cin.clear();
			 cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 choice = -1;
		 }
		 cin.ignore();

		if (choice == 1) {
			 cout << "Nhập họ tên bạn đọc: ";
			 string name;
			 getline(cin, name);
			 if (name.empty()) {
				 cout << "❌ Tên không được rỗng!\n";
			 } else {
				 manager.addReader(name);
			 }
		 } else if (choice == 2) {
			 manager.printReaders();
		} else if (choice == 3) {
			cout << "Nhập tên cần tìm (khớp chính xác theo tên): ";
			string q;
			getline(cin, q);
			auto found = manager.findByName(q);
			if (found.empty()) {
				cout << "(Không tìm thấy)\n";
			} else {
				setColor(11);
				cout << "\n--- KẾT QUẢ TÌM KIẾM ---\n";
				resetColor();
				for (auto &r : found) {
					cout << r.id << " | " << r.fullName << " | đăng ký: " << r.registeredAt << "\n";
				}
			}
		 } else if (choice == 0) {
			 cout << "⬅️  Trở về menu chính.\n";
		 } else {
			 cout << "❌ Lựa chọn không hợp lệ!\n";
		 }
	 } while (choice != 0);
 }
