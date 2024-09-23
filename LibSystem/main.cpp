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

void printDatabase(const BookDatabase& bookDb, const UserDatabase& userDb) {
    std::cout << "Books in the database:\n";
    for (const auto& book : bookDb.books) {
        std::cout << "Title: " << book.title << ", Author: " << book.author
                  << ", Release: " << book.release << ", Available: " << book.available << "\n";
    }

    std::cout << "\nUsers in the database:\n";
    for (const auto& user : userDb.users) {
        std::cout << "Name: " << user.name << ", Phone: " << user.phone << ", Email: " << user.email << "\n";
        for (const auto& borrowed : user.borrowedBooks) {
            std::cout << "  Borrowed: " << borrowed.title << ", From: " << borrowed.hasFrom
                      << ", Return: " << borrowed.returnDate << "\n";
        }
    }
}

int main() {
    BookDatabase bookDb;
    UserDatabase userDb;

    addBook(bookDb, "Kniha 1", "Janko Hrasko", "2005", true);
    addBook(bookDb, "Kniha 2", "Janko Hrasko", "2018", false);

    addUser(userDb, "John Doe", "0905 105 615", "j.doe@gmail.com");
    addBorrowedBook(userDb.users[0], "Kniha 1", "1-9-2024", "18-9-2024");
    
    printDatabase(bookDb, userDb);

    return 0;
}
