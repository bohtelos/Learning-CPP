#include <iostream>
#include <string>

bool isValidPassword(const std::string& password) {
    return password.length() >= 8;
}

int main() {

    std::string userPassword = "";

    while (!isValidPassword(userPassword)) {

        std::cout << "Enter a password: ";
        std::cin >> userPassword;

        if (!isValidPassword(userPassword)) {

            std::cout << "Too short! Try again.\n";

        }

    }

    std::cout << "Password is strong!\n";

    return 0;

}
