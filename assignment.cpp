#include <iostream>
using namespace std;
class LibraryResource {
protected:
    int resourceID;
    string title;
    string author;
    bool isAvailable;

public:
    LibraryResource(int id = 0, string t = "", string a = "") {
        resourceID = id;
        title = t;
        author = a;
        isAvailable = true;
    }

    int    getID() { return resourceID; }
    string getTitle() { return title; }
    bool   getAvailability() { return isAvailable; }

    void setAvailability(bool isAvailable) {
        this->isAvailable = isAvailable;
    }

    void displayDetails() {
        cout << "ID: " << resourceID << " | Title: " << title << " | Author: " << author << " | Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    int calculateLateFee(int daysLate) {
        return;
    }
};


class Book : public LibraryResource {
    string ISBN;
    int pageCount;
public:
    Book(int id = 0, string t = "", string a = "", string isbn = "", int pages = 0)
        : LibraryResource(id, t, a) {
        ISBN = isbn;
        pageCount = pages;
    }
    void displayDetails() {
        LibraryResource::displayDetails();
        cout << "   [Book] ISBN: " << ISBN << " | Pages: " << pageCount << endl;
    }
    int calculateLateFee(int daysLate) {
        return daysLate * 5;
    }
};

class Magazine : public LibraryResource {
    int issueNumber;
public:
    Magazine(int id = 0, string t = "", string a = "", int issue = 0)
        : LibraryResource(id, t, a) {
        issueNumber = issue;
    }
    void displayDetails() {
        LibraryResource::displayDetails();
        cout << "   [Magazine] Issue: " << issueNumber << endl;
    }
    int calculateLateFee(int daysLate) {
        return daysLate * 3;
    }
};

class DVD : public LibraryResource {
    int duration;
public:
    DVD(int id = 0, string t = "", string a = "", int dur = 0)
        : LibraryResource(id, t, a) {
        duration = dur;
    }
    void displayDetails() {
        LibraryResource::displayDetails();
        cout << "   [DVD] Duration: " << duration << " mins" << endl;
    }
    int calculateLateFee(int daysLate) {
        return daysLate * 10;
    }
};

class LibraryMember {
    int memberID;
    string name;
    LibraryResource borrowedItems[10];
    int itemCount;

public:
    LibraryMember(int id = 0, string n = "") {
        memberID = id;
        name = n;
        itemCount = 0;
    }

    int    getID() { return memberID; }
    string getName() { return name; }

    void borrowResource(LibraryResource res) {
        if (!res.getAvailability()) {
            cout << "Already borrowed!\n";
            return;
        }
        if (itemCount >= 10) {
            cout << "Borrow limit reached!\n";
            return;
        }
        res.setAvailability(false);
        borrowedItems[itemCount++] = res;
        cout << "Borrowed: " << res.getTitle() << endl;
    }

    void returnResource(int id) {
        for (int i = 0; i < itemCount; i++) {
            if (borrowedItems[i].getID() == id) {
                for (int j = i; j < itemCount - 1; j++)
                    borrowedItems[j] = borrowedItems[j + 1];
                itemCount--;
                cout << "Returned successfully!\n";
                return;
            }
        }
        cout << "Item not found!\n";
    }

    void displayBorrowedItems() {
        if (itemCount == 0) 
        { cout << "  Nothing borrowed.\n"; 
        return;
        }
        for (int i = 0; i < itemCount; i++)
            borrowedItems[i].displayDetails();
    }

    int calculateTotalLateFee(int daysLate) {
        int total = 0;
        for (int i = 0; i < itemCount; i++)
            total += borrowedItems[i].calculateLateFee(daysLate);
        return total;
    }

    friend void adminView(Library&, LibraryMember[], int);
};

class Library {
    LibraryResource resources[20];
    int resourceCount;

public:
    Library()
    { 
        resourceCount = 0; 
    }

    void addResource(LibraryResource res)
    {
        resources[resourceCount++] = res;
        cout << "Resource added!\n";
    }

    LibraryResource* findResource(int id) {
        for (int i = 0; i < resourceCount; i++)
            if (resources[i].getID() == id)
                return &resources[i];
        return NULL;
    }

    void displayResources() {
        for (int i = 0; i < resourceCount; i++)
            resources[i].displayDetails();
    }

    friend void adminView(Library&, LibraryMember[], int);
};


void adminView(Library& lib, LibraryMember members[], int count) {
    cout << "\n==== ADMIN VIEW ====\n";
    cout << "-- All Resources --\n";
    for (int i = 0; i < lib.resourceCount; i++)
        lib.resources[i].displayDetails();

    cout << "-- All Members --\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << members[i].getID() << " | Name: " << members[i].getName() << endl;
        members[i].displayBorrowedItems();
    }
    cout << "====================\n";
}

int main() {
    Library lib;
    LibraryMember members[10];
    int memberCount = 0, choice;

    do {
        cout << "\n1.Add Resource \n 2.Register Member \n 3.Borrow  4.Return\n 5.Show Resources\n  6.Member Items\n  7.Late Fee \n 8.Admin\n  9.Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int type, id; string t, a;
            cout << "Type(1=Book 2=Magazine 3=DVD): "; cin >> type;
            cout << "ID: "; cin >> id;
            cout << "Title: "; cin >> t;
            cout << "Author: "; cin >> a;
            if (type == 1) {
                string isbn; int pages;
                cout << "ISBN: "; cin >> isbn;
                cout << "Pages: "; cin >> pages;
                lib.addResource(Book(id, t, a, isbn, pages));
            }
            else if (type == 2) {
                int issue; cout << "Issue No: "; cin >> issue;
                lib.addResource(Magazine(id, t, a, issue));
            }
            else {
                int dur; cout << "Duration(mins): "; cin >> dur;
                lib.addResource(DVD(id, t, a, dur));
            }
        }
        else if (choice == 2) {
            int id; string n;
            cout << "Member ID: "; cin >> id;
            cout << "Name: "; cin >> n;
            members[memberCount++] = LibraryMember(id, n);
            cout << "Member registered!\n";
        }
        else if (choice == 3) {
            int mid, rid;
            cout << "Member ID: "; cin >> mid;
            cout << "Resource ID: "; cin >> rid;
            bool found = false;
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getID() == mid) {
                    found = true;
                    LibraryResource* res = lib.findResource(rid);
                    if (res) { members[i].borrowResource(*res); res->setAvailability(false); }
                    else cout << "Resource not found!\n";
                }
            }
            if (!found) cout << "Member not found!\n";
        }
        else if (choice == 4) {
            int mid, rid;
            cout << "Member ID: "; cin >> mid;
            cout << "Resource ID: "; cin >> rid;
            bool found = false;
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getID() == mid) {
                    found = true;
                    members[i].returnResource(rid);
                    LibraryResource* res = lib.findResource(rid);
                    if (res) res->setAvailability(true);
                }
            }
            if (!found) cout << "Member not found!\n";
        }
        else if (choice == 5) { lib.displayResources(); }
        else if (choice == 6) {
            int id; cout << "Member ID: "; cin >> id;
            bool found = false;
            for (int i = 0; i < memberCount; i++)
                if (members[i].getID() == id) { found = true; members[i].displayBorrowedItems(); }
            if (!found) cout << "Member not found!\n";
        }
        else if (choice == 7) {
            int id, days;
            cout << "Member ID: "; cin >> id;
            cout << "Days Late: "; cin >> days;
            bool found = false;
            for (int i = 0; i < memberCount; i++)
                if (members[i].getID() == id) {
                    found = true;
                    cout << "Fee: Rs." << members[i].calculateTotalLateFee(days) << endl;
                }
            if (!found) cout << "Member not found!\n";
        }
        else if (choice == 8) { adminView(lib, members, memberCount); }
        else if (choice != 9) { cout << "Invalid choice!\n"; }

    } while (choice != 9);

    cout << "Goodbye!\n";
    return 0;
}