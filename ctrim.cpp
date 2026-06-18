#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line;

    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string word;
        bool first = true;

        while (ss >> word) {
            if (!first) std::cout << " "; //
            std::cout << word;
            first = false;
        }
        std::cout << "\n";
    }
    return 0;
}
