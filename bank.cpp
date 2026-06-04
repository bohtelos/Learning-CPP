#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <string>
#include <vector>

struct Account {
    std::string name;
    double balance;
    int accountNumber;
};

int main() {
    std::vector<Account> accounts;

    std::ifstream inFile("accounts.txt");
    if (inFile.is_open()) {

        int accountNumber;
        std::string name;
        double balance;

        while (inFile >> accountNumber >> name >> balance) {
            Account tempAccount;
            tempAccount.accountNumber = accountNumber;
            tempAccount.name = name;
            tempAccount.balance = balance;

            accounts.push_back(tempAccount);
        }

        inFile.close();

    }

    bool keepGoing = true;
    int nextAccountNumber = accounts.size() + 1;

    while (keepGoing) {
        std::cout << "\n---- Bank Menu----\n";
        std::cout << "1 - Create an Account\n";
        std::cout << "2 - View All Accounts\n";
        std::cout << "3 - Deposit\n";
        std::cout << "4 - Withdraw\n";
        std::cout << "5 - Exit\n";

        int choice;
        std::cin >> choice;
        std::cin.ignore();
        
        if (std::cin.fail()) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input!\n";
            continue;
   }

        if (choice == 1) {
            std::cout << "Enter name: \n";
            std::string name;
            std::getline(std::cin, name);

            while (name.empty()) {
                std::cout << "Name cannot be empty!\n";
                std::cout << "Enter name: \n";
                std::getline(std::cin, name);
}

            Account newAccount;
            newAccount.accountNumber = nextAccountNumber;
            newAccount.name = name;
            newAccount.balance = 0.0;

            accounts.push_back(newAccount);
            nextAccountNumber++;

            std::cout << "Account created! Account number: " << newAccount.accountNumber << "\n";
        }

        else if (choice == 2) {
            std::cout << "\n---- All Accounts ----\n";
            for (const Account& account : accounts) {
                std::cout << account.accountNumber << ". ";
                std::cout << account.name << " - $";
                std::cout << account.balance << "\n";
            }
        }

        else if (choice == 3) {

        std::cout << "Enter account number: \n";
        int accountNumber;
        std::cin >> accountNumber;
        std::cin.ignore();

        int foundIndex = -1;
        for (int i = 0; i < accounts.size(); i++) {

            if (accounts[i].accountNumber == accountNumber) {

                foundIndex = i;
                break;

        }

    }

       if (foundIndex == -1) {

            std::cout << "Account not found.\n";

    }

    else {

        std::cout << "Enter amount to deposit: $";
        double amount;
        std::cin >> amount;

        while (amount <= 0 || std::cin.fail()) {
            std::cout << "Invalid amount! Enter valid number: $";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> amount;
        }

        accounts[foundIndex].balance += amount;

        std::cout << "Deposit successful!\n";
        std::cout << "New balance: $" << accounts[foundIndex].balance << "\n";

    }

}

        else if (choice == 4) {

        std::cout << "Enter account number: \n";
        int accountNumber;
        std::cin >> accountNumber;
        std::cin.ignore();

        int foundIndex = -1;
        for (int i = 0; i < accounts.size(); i++) {

            if (accounts[i].accountNumber == accountNumber) {

                foundIndex = i;
                break;

        }

    }

    if (foundIndex == -1) {

        std::cout << "Account not found.\n";

    }

    else {

        std::cout << "Enter amount to withdraw: $";
        double amount;
        std::cin >> amount;

        while (amount <= 0 || std::cin.fail()) {
            std::cout << "Invalid amount! Enter valid number: $";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> amount;
        }

        if (amount > accounts[foundIndex].balance) {
            std::cout << "Insufficient funds!\n";
        }
        else {
            accounts[foundIndex].balance -= amount;
            std::cout << "Withdrawal successful!\n";
            std::cout << "New balance: $" << accounts[foundIndex].balance << "\n";
        }

    }


}

        else if (choice == 5) {
            keepGoing = false;
            std::cout << "Logged out.\n";
        }
    }

    std::ofstream outFile("accounts.txt");
    if (outFile.is_open()) {
        for (const Account& account : accounts) {
            outFile << account.accountNumber << " " << account.name << " " << account.balance << "\n";
        }

        outFile.close();

    }

    return 0;
}

