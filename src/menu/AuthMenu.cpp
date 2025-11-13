 #include "AuthMenu.h"
 #include "../managers/AuthManager.h"
 #include "../utils/color_utils.h"
 #include <iostream>
 #include <limits>
 using namespace std;

 bool AuthMenu::show() {
	 AuthManager auth;
	 int choice;
	 while (true) {
		 setColor(11);
		 cout << "\n===== XÁC THỰC HỆ THỐNG =====\n"; resetColor();
		 cout << "1. Đăng nhập\n";
		 cout << "2. Đăng ký tài khoản mới\n";
		 cout << "0. Thoát\n";
		 cout << "==============================\n";
		 cout << "Nhập lựa chọn: ";
		 if (!(cin >> choice)) {
			 cin.clear();
			 cin.ignore(numeric_limits<streamsize>::max(), '\n');
			 choice = -1;
		 }
		 cin.ignore();

		 if (choice == 1) {
			 if (auth.login()) return true; // nếu login thành công => vào hệ thống
		 } else if (choice == 2) {
			 auth.registerUser();
		 } else if (choice == 0) {
			 cout << "👋 Thoát chương trình.\n"; return false;
		 } else {
			 cout << "❌ Lựa chọn không hợp lệ!\n";
		 }
	 }
 }
