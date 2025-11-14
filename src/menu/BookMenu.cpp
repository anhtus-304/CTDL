#include "BookMenu.h"
#include "../managers/BookManager.h"
#include "../utils/color_utils.h"
#include <iostream>

using namespace std;

void BookMenu::show() {
    BookManager bookManager;
    
    if (!bookManager.initialize()) {
        setColor(12);
        cout << " Lỗi khi tải dữ liệu sách!\n";
        resetColor();
        return;
    }
    
    int choice;
    do {
        setColor(14);
        cout << "\n📚 QUẢN LÝ SÁCH\n";
        cout << "1. Hiển thị danh sách sách\n";
        cout << "2. Thêm sách mới\n";
        cout << "3. Xóa sách\n";
        cout << "0. Quay lại menu chính\n";
        cout << "Chọn chức năng: ";
        resetColor();
        
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                bookManager.displayAllBooks();
                break;
            case 2:
                bookManager.addBook();
                break;
            case 3:
                bookManager.deleteBook();
                break;
            case 0:
                setColor(10);
                cout << "👋 Quay lại menu chính...\n";
                resetColor();
                break;
            default:
                setColor(12);
                cout << " Lựa chọn không hợp lệ!\n";
                resetColor();
                break;
        }
    } while (choice != 0);
}