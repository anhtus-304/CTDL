#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string id;
    string title;
    string author;
    string publisher;
    double price;
    int publishYear;
    int pageCount;
    string importDate;
    int status;

public:
    Book();
    
    string getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }
    double getPrice() const { return price; }
    int getPublishYear() const { return publishYear; }
    int getPageCount() const { return pageCount; }
    string getImportDate() const { return importDate; }
    int getStatus() const { return status; }
    
    void setStatus(int newStatus) { status = newStatus; }
    
    bool isAvailable() const { return status == 0; }
    string toString() const;
    static Book fromString(const string& line);
    bool isValid() const;
};

#endif