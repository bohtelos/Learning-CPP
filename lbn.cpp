#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "No search argument\n";
        return 1;
    }

    std::string searchWord = argv[1];
    std::string currentLine;

    while (std::getline(std::cin, currentLine)) {
        if (currentLine.find(searchWord) != std::string::npos) {
            std::cout << currentLine << "\n";
        }
    }

    return 0;

}
