#include <iostream>
#include <string>

int main() {
    int lineCount = 0;
    std::string currentLine;

    while (std::getline(std::cin, currentLine)) {
        lineCount++;
    }

    std::cout << lineCount << "\n";

    return 0;
}
