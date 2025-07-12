#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    int id;
    string title, author;
    bool isIssued;

    Book() {}

    Book(int bookId, string bookTitle, string bookAuthor, bool issued = false) {
        id = bookId;
        title = bookTitle;
        author = bookAuthor;
        isIssued = issued;
    }

    void display() {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    const string filename = "books.txt";

    void loadBooksFromFile() {
        ifstream file(filename);
        if (!file) return;

        books.clear();
        int id;
        string title, author;
        bool isIssued;

        while (file >> id) {
            file.ignore();
            getline(file, title);
            getline(file, author);
            file >> isIssued;
            books.push_back(Book(id, title, author, isIssued));
        }
        file.close();
    }

    void saveBooksToFile() {
        ofstream file(filename);
        for (Book &book : books) {
            file << book.id << endl;
            file << book.title << endl;
            file << book.author << endl;
            file << book.isIssued << endl;
        }
        file.close();
    }

public:
    Library() {
        loadBooksFromFile();
    }

    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        saveBooksToFile();
        cout << "Book added successfully!\n";
    }

    void showAllBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        for (Book &book : books) {
            book.display();
        }
    }

    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;
        for (Book &book : books) {
            if (book.id == id) {
                book.display();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void deleteBook() {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                books.erase(it);
                saveBooksToFile();
                cout << "Book deleted successfully.\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n2. Show All Books\n3. Search Book\n4. Delete Book\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.showAllBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.deleteBook(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
