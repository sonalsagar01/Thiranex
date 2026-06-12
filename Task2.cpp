#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNo;
    char name[50];
    float balance;

public:
    void createAccount()
    {
        cout << "Enter Account Number: ";
        cin >> accountNo;
        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;
    }

    void showAccount() const
    {
        cout << "\nAccount Number : " << accountNo;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : Rs. " << balance << endl;
    }

    int getAccountNo() const
    {
        return accountNo;
    }

    void deposit(float amount)
    {
        balance += amount;
    }

    bool withdraw(float amount)
    {
        if (amount > balance)
        {
            return false;
        }
        balance -= amount;
        return true;
    }

    float getBalance() const
    {
        return balance;
    }
};

// Create New Account
void createNewAccount()
{
    BankAccount acc;

    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    outFile.write((char *)&acc, sizeof(acc));

    outFile.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display Account Details
void displayAccount(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream inFile("bank.dat", ios::binary);

    while (inFile.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNo() == accNo)
        {
            acc.showAccount();
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit Amount
void depositAmount(int accNo)
{
    BankAccount acc;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNo() == accNo)
        {
            float amount;

            cout << "Enter Deposit Amount: ";
            cin >> amount;

            acc.deposit(amount);

            int pos = -1 * sizeof(acc);
            file.seekp(pos, ios::cur);

            file.write((char *)&acc, sizeof(acc));

            cout << "\nAmount Deposited Successfully!\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Withdraw Amount
void withdrawAmount(int accNo)
{
    BankAccount acc;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNo() == accNo)
        {
            float amount;

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (acc.withdraw(amount))
            {
                int pos = -1 * sizeof(acc);
                file.seekp(pos, ios::cur);

                file.write((char *)&acc, sizeof(acc));

                cout << "\nWithdrawal Successful!\n";
            }
            else
            {
                cout << "\nInsufficient Balance!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Check Balance
void checkBalance(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    while (file.read((char *)&acc, sizeof(acc)))
    {
        if (acc.getAccountNo() == accNo)
        {
            cout << "\nCurrent Balance: Rs. "
                 << acc.getBalance() << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice, accNo;

    do
    {
        cout << "\n================================";
        cout << "\n BANK MANAGEMENT SYSTEM";
        cout << "\n================================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display Account Details";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accNo;
            depositAmount(accNo);
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            withdrawAmount(accNo);
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            checkBalance(accNo);
            break;

        case 5:
            cout << "Enter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}