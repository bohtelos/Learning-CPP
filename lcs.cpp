#include <iostream>
#include <string>

int main() {

    int lineCount = 0;
    int charCount = 0;
    int maxLength = 0;

    std::string currentLine;

    while (std::getline(std::cin, currentLine)) {
        lineCount++;
        charCount = charCount + currentLine.length();

        if (currentLine.length() > maxLength) {
            maxLength = currentLine.length();
        }

    }

    std::cout << "\n---- Text Statistics ----\n";
    std::cout << "Lines processed: " << lineCount << "\n";
    std::cout << "Total characters: " << charCount << "\n";
    std::cout << "Longest line:   " << maxLength << " chars\n";

    return 0;

}
