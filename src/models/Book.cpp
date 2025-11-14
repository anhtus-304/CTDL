#include "Book.h"
#include "../utils/string_utils.h"
#include <sstream>

using namespace std;

Book::Book() : price(0), publishYear(0), pageCount(0), status(0) {}

string Book::toString() const {
    return id + "," + title + "," + author + "," + publisher + "," +
           to_string(price) + "," + to_string(publishYear) + "," +
           to_string(pageCount) + "," + importDate + "," +
           to_string(status);
}

Book Book::fromString(const string& line) {
    Book book;
    auto parts = split(line, ',');
    
    if (parts.size() >= 9) {
        book.id = trim(parts[0]);
        book.title = trim(parts[1]);
        book.author = trim(parts[2]);
        book.publisher = trim(parts[3]);
        book.price = stod(trim(parts[4]));
        book.publishYear = stoi(trim(parts[5]));
        book.pageCount = stoi(trim(parts[6]));
        book.importDate = trim(parts[7]);
        book.status = stoi(trim(parts[8]));
    }
    
    return book;
}

bool Book::isValid() const {
    return !id.empty() && !title.empty() && price >= 0 && 
           publishYear > 0 && pageCount > 0 && status >= 0;
}