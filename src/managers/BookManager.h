#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include "../models/Book.h"
#include <vector>
#include <string>
using namespace std;

class BookManager {
private:
    vector<Book> books;
    string dataFile = "data/Sach.txt";
    
    bool saveToFile();
    bool loadFromFile();
    int findBookById(const string& id) const;

public:
    BookManager();
    bool initialize();
    
    void displayAllBooks();
    bool addBook();
    bool deleteBook();
    Book* getBookById(const string& id);
    void updateBookStatus(const string& bookId, int status);
};

#endif