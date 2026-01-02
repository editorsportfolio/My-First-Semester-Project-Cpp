#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;


class Book {
private:
    string title;
    string author;
    int id;
    bool isIssued;
    string issueDate;
    string returnDate;

public:
	//constructor to initialize a book
    Book(int id, string title, string author) 
        : id(id), title(title), author(author), isIssued(false), issueDate(""), returnDate("") {}

    
    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }
    string getIssueDate() const { return issueDate; }
    string getReturnDate() const { return returnDate; }

    
    void setIssued(bool issued) { isIssued = issued; }
    void setIssueDate(const string& date) { issueDate = date; } //sets issued date of the book
    void setReturnDate(const string& date) { returnDate = date; }
};


class User {
private:
    string name;
    int userId;

public:
    User(int userId, string name) : userId(userId), name(name) {}

    string getName() const { return name; }
    int getUserId() const { return userId; }
};


class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));   //Add a new book to the vector
        cout << "Book added: " << title << " by " << author << endl;
    }

    
    void addUser(int userId, string name) {
        users.push_back(User(userId, name)); //Add a new user to the vector
        cout << "User added: " << name << endl;
    }
void displayIssuedBooks() {
    bool found = false;
    for (const auto& book : books) {
        if (book.getIsIssued()) {
            cout << book.getTitle() << " is issued (Return by "
                 << book.getReturnDate() << ")" << endl;
            found = true;
        }
    }
    if (!found) cout << "No books are currently issued." << endl;
}

    //find the book and the user
    void issueBook(int bookId, int userId, const string& issueDate, const string& returnDate) {
        for (auto& book : books) {  //loop through all books
            if (book.getId() == bookId && !book.getIsIssued()) {
                for (auto& user : users) {
                    if (user.getUserId() == userId) { //issue the book to the user
                        book.setIssued(true);
                        book.setIssueDate(issueDate);
                        book.setReturnDate(returnDate);
                        cout << "Book issued to " << user.getName() << ". Return by " << returnDate << endl;
                        return;
                    }
                }
                cout << "User not found!" << endl;
                return;
            }
        }
        cout << "Sorry, The book you are currently trying to access is not available for issuing!" << endl;
    }
    // Return a book
    void returnBook(int bookId, int userId) {
        for (auto& book : books) {
            if (book.getId() == bookId && book.getIsIssued()) {
                book.setIssued(false);
                book.setIssueDate("");
                book.setReturnDate("");
                cout << "Book returned successfully, thank you!" << endl;
                return;
            }
        }
        cout << "Invalid book return!" << endl;
    }

    //Search books by title
    void searchByTitle(const string& title) {
        bool found = false;
        for (const auto& book : books) {
            if (book.getTitle() == title) {
                cout << "Found book: " << book.getTitle() << " by " << book.getAuthor() << endl;
                found = true;
            }
        }
        if (!found) cout << "Unfortuantely, No books were found with that title." << endl;
    }

    // Search books by author
    void searchByAuthor(const string& author) {
        bool found = false;
        for (const auto& book : books) {
            if (book.getAuthor() == author) {
                cout << "Found book: " << book.getTitle() << " by " << book.getAuthor() << endl;
                found = true;
            }
        }
        if (!found) cout << "No books found by that author. You can add that book, if you want!" << endl;
    }

    // Display all books
    void displayBooks() {
        if (books.empty()) {
            cout << "No books available in the library!" << endl;
            return;
        }
        for (const auto& book : books) {
            cout << "Book ID: " << book.getId() << ", Title: " << book.getTitle() 
                 << ", Author: " << book.getAuthor() 
                 << ", Issued: " << (book.getIsIssued() ? "Yes" : "No") << endl;
        }
    }
};


int main() {
    Library library;

    
    library.addBook(1, "Math Magic", "Sarah Green");
    library.addBook(2, "Code Basics", "John Smith");
    library.addBook(3, "Physics Fun ", "Emma Blue");

    
    library.addUser(1, "Misbah");
    library.addUser(2, "Nimra");

    int choice;
    while (true) {
        cout << "\nLibrary Management System"<<endl;
        cout << "1. Add Book"<<endl;
        cout << "2. Add User"<<endl;
        cout << "3. Issue Book"<<endl;
        cout << "4. Return Book"<<endl;
        cout << "5. Search Book by Title"<<endl;
        cout << "6. Search Book by Author"<<endl;
        cout << "7. Display All Books"<<endl;
        cout << "8. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Book Title: ";
            cin.ignore();  
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            library.addBook(id, title, author);
        } 
        else if (choice == 2) {
            int userId;
            string name;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter User Name: ";
            cin.ignore();
            getline(cin, name);
            library.addUser(userId, name);
        }
        else if (choice == 3) {
            int bookId, userId;
            string issueDate, returnDate;
            cout << "Enter Book ID to Issue: ";
            cin >> bookId;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Issue Date (YYYY-MM-DD): ";
            cin.ignore();
            getline(cin, issueDate);
            cout << "Enter Return Date (YYYY-MM-DD): ";
            getline(cin, returnDate);
            library.issueBook(bookId, userId, issueDate, returnDate);
        }
        else if (choice == 4) {
            int bookId, userId;
            cout << "Enter Book ID to Return: ";
            cin >> bookId;
            cout << "Enter User ID: ";
            cin >> userId;
            library.returnBook(bookId, userId);
        }
        else if (choice == 5) {
            string title;
            cout << "Enter Book Title to Search: ";
            cin.ignore();
            getline(cin, title);
            library.searchByTitle(title);
        }
        else if (choice == 6) {
            string author;
            cout << "Enter Book Author to Search: ";
            cin.ignore();
            getline(cin, author);
            library.searchByAuthor(author);
        }
        else if (choice == 7) {
            library.displayBooks();
        }
        else if (choice == 8) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    }

    return 0;
}
