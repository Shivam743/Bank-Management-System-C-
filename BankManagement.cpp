#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Account structure
struct Account
{
    int accNo;
    double balance;
};

// Global storage
vector<Account> accounts;
int nextAccountNumber = 1000; // starting account number

// Load accounts from file
void loadFromFile()
{
    ifstream file("accounts.txt");
    Account a;
    int maxAcc = nextAccountNumber;

    while (file >> a.accNo >> a.balance)
    {
        accounts.push_back(a);
        if (a.accNo >= maxAcc)
            maxAcc = a.accNo + 1;
    }

    nextAccountNumber = maxAcc;
    file.close();
}

// Save accounts to file
void saveToFile()
{
    ofstream file("accounts.txt");
    for (auto &a : accounts)
    {
        file << a.accNo << " " << a.balance << endl;
    }
    file.close();
}

// Find account index
int findAccount(int accNo)
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].accNo == accNo)
            return i;
    }
    return -1;
}

// Create account (AUTO account number)
void createAccount()
{
    double bal;

    cout << "Generated Account Number: " << nextAccountNumber << endl;
    cout << "Enter Initial Balance: ";
    cin >> bal;

    if (bal < 0)
    {
        cout << "Initial balance cannot be negative\n";
        return;
    }

    accounts.push_back({nextAccountNumber, bal});
    nextAccountNumber++;

    saveToFile();
    cout << "Account created successfully\n";
}

// Deposit money
void deposit()
{
    int acc;
    double amt;

    cout << "Enter Account Number: ";
    cin >> acc;

    int index = findAccount(acc);
    if (index == -1)
    {
        cout << "Account not found\n";
        return;
    }

    cout << "Enter Amount to Deposit: ";
    cin >> amt;

    if (amt <= 0)
    {
        cout << "Invalid amount\n";
        return;
    }

    accounts[index].balance += amt;
    saveToFile();
    cout << "Deposit successful\n";
}

// Withdraw money
void withdrawMoney()
{
    int acc;
    double amt;

    cout << "Enter Account Number: ";
    cin >> acc;

    int index = findAccount(acc);
    if (index == -1)
    {
        cout << "Account not found\n";
        return;
    }

    cout << "Enter Amount to Withdraw: ";
    cin >> amt;

    if (amt <= 0)
    {
        cout << "Invalid amount\n";
        return;
    }

    if (accounts[index].balance < amt)
    {
        cout << "Insufficient balance\n";
        return;
    }

    accounts[index].balance -= amt;
    saveToFile();
    cout << "Withdraw successful\n";
}

// Check balance
void checkBalance()
{
    int acc;
    cout << "Enter Account Number: ";
    cin >> acc;

    int index = findAccount(acc);
    if (index == -1)
    {
        cout << "Account not found\n";
        return;
    }

    cout << "Current Balance: " << accounts[index].balance << endl;
}

// Show all accounts
void showAllAccounts()
{
    if (accounts.empty())
    {
        cout << "No accounts found\n";
        return;
    }

    cout << "\nAccount No\tBalance\n";
    cout << "----------------------\n";
    for (auto &a : accounts)
    {
        cout << a.accNo << "\t\t" << a.balance << endl;
    }
}

int main()
{
    loadFromFile();

    int choice;
    do
    {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Show All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            showAllAccounts();
            break;
        case 6:
            cout << "Thank you. Exiting...\n";
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 6);

    return 0;
}
