#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book Class
class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        issued = false;
    }
};

// Member Class
class Member {
public:
    int memberId;
    string memberName;

    Member(int id, string name) {
        memberId = id;
        memberName = name;
    }
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:

    // Add Book
    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));

        cout << "Book Added Successfully!\n";
    }

    // Display Books
    void displayBooks() {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        cout << "\n--- Book List ---\n";

        for (auto &book : books) {
            cout << "ID: " << book.id
                 << " | Title: " << book.title
                 << " | Author: " << book.author
                 << " | Status: " << (book.issued ? "Issued" : "Available")
                 << endl;
        }
    }

    // Search by Title
    void searchByTitle() {
        string title;
        cin.ignore();

        cout << "Enter Title to Search: ";
        getline(cin, title);

        bool found = false;

        for (auto &book : books) {
            if (book.title == title) {
                cout << "Book Found:\n";
                cout << "ID: " << book.id
                     << " | Author: " << book.author
                     << " | Status: "
                     << (book.issued ? "Issued" : "Available")
                     << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Book not found.\n";
        }
    }

    // Search by Author
    void searchByAuthor() {
        string author;
        cin.ignore();

        cout << "Enter Author Name: ";
        getline(cin, author);

        bool found = false;

        for (auto &book : books) {
            if (book.author == author) {
                cout << "Book Found:\n";
                cout << "ID: " << book.id
                     << " | Title: " << book.title
                     << " | Status: "
                     << (book.issued ? "Issued" : "Available")
                     << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "No books found for this author.\n";
        }
    }

    // Issue Book
    void issueBook() {
        int id;

        cout << "Enter Book ID to Issue: ";
        cin >> id;

        for (auto &book : books) {
            if (book.id == id) {

                if (book.issued) {
                    cout << "Book is already issued.\n";
                } else {
                    book.issued = true;
                    cout << "Book Issued Successfully!\n";
                }
                return;
            }
        }

        cout << "Book not found.\n";
    }

    // Return Book
    void returnBook() {
        int id;

        cout << "Enter Book ID to Return: ";
        cin >> id;

        for (auto &book : books) {
            if (book.id == id) {

                if (!book.issued) {
                    cout << "Book was not issued.\n";
                } else {
                    book.issued = false;
                    cout << "Book Returned Successfully!\n";
                }
                return;
            }
        }

        cout << "Book not found.\n";
    }
};

// Main Function
int main() {

    Library lib;
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            lib.addBook();
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            lib.searchByTitle();
            break;

        case 4:
            lib.searchByAuthor();
            break;

        case 5:
            lib.issueBook();
            break;

        case 6:
            lib.returnBook();
            break;

        case 7:
            cout << "Exiting Program...\n";
            break;

        default:
            cout << "Invalid Choice.\n";
        }

    } while (choice != 7);

    return 0;
}