#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BorrowedBook {
    std::string title;
    std::string hasFrom;
    std::string returnDate;
};

struct Book {
    std::string title;
    std::string author;
    std::string release;
    bool available;
};

struct User {
    std::string name;
    std::string phone;
    std::string email;
    std::vector<BorrowedBook> borrowedBooks;
};

struct BookDatabase {
    std::vector<Book> books;
};

struct UserDatabase {
    std::vector<User> users;
};

void addBook(BookDatabase& db, const string& title, const string& author, const string& release, bool available) {
    Book book{title, author, release, available};
    db.books.push_back(book);
}

void addUser(UserDatabase& db, const string& name, const string& phone, const string& email) {
    User user{name, phone, email};
    db.users.push_back(user);
}

void addBorrowedBook(User& user, const string& title, const string& hasFrom, const string& returnDate) {
    BorrowedBook borrowed{title, hasFrom, returnDate};
    user.borrowedBooks.push_back(borrowed);
}

int main() {


    return 0;
}