#include <iostream>
#include <string>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

using namespace std;

struct Check {
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    // Overloaded comparison operator
    bool operator>(float amount) {
        return CheckAmount > amount;
    }

    // Overloaded << operator
    friend ostream& operator<<(ostream& os, const Check& check) {
        os << "Check Number: " << check.CheckNum << ", Memo: " << check.CheckMemo << ", Amount: " << check.CheckAmount;
        return os;
    }
};

class CheckBook {
private:
    float balance;
    Check* chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;

public:
    // Constructors
    CheckBook() : balance(0), chkPtr(nullptr), lastDeposit(0), numOfChecks(0), checkBookSize(4) {
        chkPtr = new Check[checkBookSize];
    }

    CheckBook(float initialBalance) : balance(initialBalance), chkPtr(nullptr), lastDeposit(0), numOfChecks(0), checkBookSize(2) {
        chkPtr = new Check[checkBookSize];
    }

    // Destructor
    ~CheckBook() {
        delete[] chkPtr;
    }

    // Copy constructor
    CheckBook(const CheckBook& other) : balance(other.balance), chkPtr(new Check[other.checkBookSize]), lastDeposit(other.lastDeposit), numOfChecks(other.numOfChecks), checkBookSize(other.checkBookSize) {
        for (int i = 0; i < numOfChecks; ++i) {
            chkPtr[i] = other.chkPtr[i];
        }
    }

    // Assignment operator
    CheckBook& operator=(const CheckBook& other) {
        if (this != &other) {
            balance = other.balance;
            lastDeposit = other.lastDeposit;
            numOfChecks = other.numOfChecks;
            checkBookSize = other.checkBookSize;

            delete[] chkPtr;
            chkPtr = new Check[checkBookSize];

            for (int i = 0; i < numOfChecks; ++i) {
                chkPtr[i] = other.chkPtr[i];
            }
        }
        return *this;
    }

    // Deposit function
    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
    }

    // WriteCheck function
    bool writeCheck(Check c_amount) {
        if (c_amount > balance) {
            return false;
        }

        if (numOfChecks >= checkBookSize / 2) {
            // Warning for new book
            cout << "Warning: Half of the check book used. New book has been ordered." << endl;
            checkBookSize *= 2;
            Check* temp = new Check[checkBookSize];
            for (int i = 0; i < numOfChecks; ++i) {
                temp[i] = chkPtr[i];
            }
            delete[] chkPtr;
            chkPtr = temp;
        }

        // Assuming memo list
        string memoList[] = {"wedding", "baby shower", "pizza", "children hospital", "barber shop", "plumber", "hobbit", "trudo"};
        int randIndex = rand() % 8; // Randomly select a memo from the list
        c_amount.CheckMemo = memoList[randIndex];

        c_amount.CheckNum = numOfChecks + 1; // Update CheckNum
        chkPtr[numOfChecks++] = c_amount;
        balance -= c_amount.CheckAmount; // Update balance
        return true;
    }

