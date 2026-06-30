#include <iostream>
#include <fstream>
#include <string>

int main() {

    // Prepare

    std::string name;
    std::string line;

    // Interaction

    std::cout << "Enter file name: \n";
    std::getline(std::cin, name);

    // Reading

    std::ifstream inFile(name);

    // Validation

    if (!inFile.is_open()) {
        std::cerr << "No such file.\n";
        return 1;
    }

    while (std::getline(inFile, line)) {

        // See out

        std::cout << line << "\n";

    }

    // End of the program

    inFile.close();

    return 0;
}
