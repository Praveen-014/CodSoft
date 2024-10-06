#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

struct Book
 {
    string title;
    string author;
    string ISBN;
    bool available;
};

    struct Borrower 
{
    string name;
    string borrowedISBN; 
    time_t borrowDate;   
};
class Library
 {
private:
    vector<Book> books;         
    vector<Borrower> borrowers;  
public:
        void addBook(const string& title, const string& author, const string& ISBN)
 {
        books.push_back({title, author, ISBN, true});
        cout << "Book added: " << title << endl;
    }

       void searchBooks(const string& query) 
{
        cout << "Search results for: " << query << endl;
        bool found = false;

        for (const auto& book : books)
 {
            if (book.title.find(query) != string::npos || 
                book.author.find(query) != string::npos || 
                book.ISBN == query) 
{
                found = true;
                cout << "Title: " << book.title << ", Author" << book.author 
                     << ", ISBN" << book.ISBN 
                     << (book.available ? " (Available)" : " (Checked Out)") << endl;
            }
        }

        if (!found) 
{
            cout << "No books found.\n";
        }
    }

    void checkoutBook(const string& ISBN, const string& borrowerName) 
{
        for (auto& book : books) 
{
            if (book.ISBN == ISBN && book.available)
 {
                book.available = false;                    borrowers.push_back({borrowerName, ISBN, time(0)}); 
                cout << "Book checked out: " << book.title << endl;
                return;
            }
        }
        cout << "Book not available for checkout.\n";
    }

    void returnBook(const string& ISBN) 
{
        for (auto& book : books)
 {
            if (book.ISBN == ISBN && !book.available)
 {
                book.available = true; 
                cout << "Book returned: " << book.title << endl;
                for (auto it = borrowers.begin(); it != borrowers.end(); ++it) 
{
                    if (it->borrowedISBN == ISBN) 
{
                        borrowers.erase(it);
                        break;
                    }
                }
                return;
            }
        }
        cout << "Book was not checked out.\n";
    }
    void calculateFine()
 {
        time_t currentTime = time(0);
        double totalFine = 0.0;
        for (const auto& borrower : borrowers)
 {
            double daysBorrowed = difftime(currentTime, borrower.borrowDate) / (60 * 60 * 24);
            if (daysBorrowed > 5) 
{
                double fine = (daysBorrowed - 5) * 1.0; // $1 per day after 5 days
                totalFine += fine;
                cout << "Borrower: " << borrower.name << ", ISBN: " << borrower.borrowedISBN 
                     << ", Fine: $" << fine << endl;
            }
        }

        if (totalFine == 0)
 {
            cout << "No overdue books.\n";
        } else {
            cout << "Total fines collected: $" << totalFine << endl;
        }
    }
};

int main()
 {
    Library library;
    int choice;
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "123456789");
    library.addBook("1984", "George Orwell", "987654321");
    library.addBook("To Kill a Mockingbird", "Harper Lee", "456789123");

    do 
{
        cout << "\nLibrary Management System\n";
        cout << "1. Search for a book\n";
        cout << "2. Check out a book\n";
        cout << "3. Return a book\n";
        cout << "4. Calculate fines for overdue books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string input;
        switch (choice)
 {
            case 1:
                cout << "Enter title, author, or ISBN to search";
                cin.ignore();
                getline(cin, input);
                library.searchBooks(input);
                break;
            case 2:
                cout << "Enter ISBN of the book to check out";
                cin >> input;
                cout << "Enter borrower's name";
                cin.ignore();
                getline(cin, input);
                library.checkoutBook(input, input);
                break;
            case 3:
                cout << "Enter ISBN of the book to return";
                cin >> input;
                library.returnBook(input);
                break;
            case 4:
                library.calculateFine();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
