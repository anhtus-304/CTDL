#include "BookManager.h"
#include "../utils/file_utils.h"
#include "../utils/string_utils.h"
#include "../utils/color_utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

BookManager::BookManager() {
    initialize();
}

bool BookManager::loadFromFile() {
    vector<string> lines = readFileLines(dataFile);
    if (lines.empty()) return true;
    
    books.clear();
    for (auto& line : lines) {
        if (!trim(line).empty()) {
            Book book = Book::fromString(line);
            if (book.isValid()) {
                books.push_back(book);
            }
        }
    }
    return true;
}

bool BookManager::saveToFile() {
    vector<string> lines;
    for (auto& book : books) {
        lines.push_back(book.toString());
    }
    writeFileLines(dataFile, lines);
    return true;
}

bool BookManager::initialize() {
    return loadFromFile();
}

int BookManager::findBookById(const string& id) const {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

void BookManager::displayAllBooks() {
    if (books.empty()) {
        setColor(14);
        cout << "📚 Danh sách sách trống!\n";
        resetColor();
        return;
    }
    
    setColor(11);
    cout << "\n📚 DANH SÁCH SÁCH TRONG THƯ VIỆN\n";
    cout << "==========================================================================================================\n";
    cout << left << setw(12) << "Mã sách" 
         << setw(25) << "Tên sách" 
         << setw(20) << "Tác giả" 
         << setw(15) << "Nhà XB" 
         << setw(10) << "Giá" 
         << setw(8) << "Năm XB" 
         << setw(8) << "Trang" 
         << setw(12) << "Ngày nhập" 
         << setw(15) << "Tình trạng" 
         << endl;
    cout << "==========================================================================================================\n";
    resetColor();
    
    for (auto& book : books) {
        cout << left << setw(12) << book.getId() 
             << setw(25) << (book.getTitle().length() > 24 ? book.getTitle().substr(0, 24) + "..." : book.getTitle())
             << setw(20) << (book.getAuthor().length() > 19 ? book.getAuthor().substr(0, 19) + "..." : book.getAuthor())
             << setw(15) << book.getPublisher() 
             << setw(10) << fixed << setprecision(0) << book.getPrice() 
             << setw(8) << book.getPublishYear() 
             << setw(8) << book.getPageCount() 
             << setw(12) << book.getImportDate();
        
        if (book.isAvailable()) {
            setColor(10);
            cout << setw(15) << "Có sẵn";
            resetColor();
        } else {
            setColor(12);
            cout << setw(15) << "Đang mượn (" + to_string(book.getStatus()) + ")";
            resetColor();
        }
        cout << endl;
    }
    
    setColor(11);
    cout << "==========================================================================================================\n";
    cout << "Tổng số sách: " << books.size() << endl;
    resetColor();
}

bool BookManager::addBook() {
    string id, title, author, publisher, priceStr, yearStr, pageStr, dateStr;
    
    setColor(14);
    cout << "\n THÊM SÁCH MỚI\n";
    resetColor();
    
    cout << "Mã sách: ";
    getline(cin, id);
    
    if (findBookById(id) != -1) {
        setColor(12);
        cout << " Mã sách đã tồn tại!\n";
        resetColor();
        return false;
    }
    
    cout << "Tên sách: ";
    getline(cin, title);
    
    cout << "Tác giả: ";
    getline(cin, author);
    
    cout << "Nhà xuất bản: ";
    getline(cin, publisher);
    
    cout << "Giá bán: ";
    getline(cin, priceStr);
    
    cout << "Năm phát hành: ";
    getline(cin, yearStr);
    
    cout << "Số trang: ";
    getline(cin, pageStr);
    
    cout << "Ngày nhập kho (dd/mm/yyyy): ";
    getline(cin, dateStr);
    
    try {
        double price = stod(priceStr);
        int year = stoi(yearStr);
        int pages = stoi(pageStr);
        
        string bookStr = id + "," + title + "," + author + "," + publisher + "," + 
                        to_string(price) + "," + to_string(year) + "," + 
                        to_string(pages) + "," + dateStr + ",0";
        Book newBook = Book::fromString(bookStr);
        
        if (!newBook.isValid()) {
            throw invalid_argument("Dữ liệu sách không hợp lệ");
        }
        
        books.push_back(newBook);
        
        if (saveToFile()) {
            setColor(10);
            cout << "✅ Thêm sách thành công!\n";
            resetColor();
            return true;
        } else {
            throw runtime_error("Lỗi khi lưu file");
        }
        
    } catch (const exception& e) {
        setColor(12);
        cout << "❌ Lỗi: " << e.what() << endl;
        resetColor();
        return false;
    }
}

bool BookManager::deleteBook() {
    setColor(14);
    cout << "\n XÓA SÁCH\n";
    resetColor();
    
    string bookId;
    cout << "Nhập mã sách cần xóa: ";
    getline(cin, bookId);
    
    int index = findBookById(bookId);
    if (index == -1) {
        setColor(12);
        cout << " Không tìm thấy sách với mã: " << bookId << endl;
        resetColor();
        return false;
    }
    
    Book& book = books[index];
    
    if (!book.isAvailable()) {
        setColor(12);
        cout << " Không thể xóa sách! Sách đang được mượn (phiếu mượn số: " << book.getStatus() << ")\n";
        resetColor();
        return false;
    }
    
    cout << "Thông tin sách sẽ xóa:\n";
    cout << "Mã sách: " << book.getId() << endl;
    cout << "Tên sách: " << book.getTitle() << endl;
    cout << "Tác giả: " << book.getAuthor() << endl;
    
    cout << "Bạn có chắc chắn muốn xóa? (y/n): ";
    string confirm;
    getline(cin, confirm);
    
    if (confirm != "y" && confirm != "Y") {
        setColor(14);
        cout << " Đã hủy thao tác xóa.\n";
        resetColor();
        return false;
    }
    
    books.erase(books.begin() + index);
    
    if (saveToFile()) {
        setColor(10);
        cout << " Xóa sách thành công!\n";
        resetColor();
        return true;
    } else {
        setColor(12);
        cout << " Lỗi khi lưu dữ liệu!\n";
        resetColor();
        return false;
    }
}

Book* BookManager::getBookById(const string& id) {
    int index = findBookById(id);
    if (index != -1) {
        return &books[index];
    }
    return nullptr;
}

void BookManager::updateBookStatus(const string& bookId, int status) {
    int index = findBookById(bookId);
    if (index != -1) {
        books[index].setStatus(status);
        saveToFile();
    }
}