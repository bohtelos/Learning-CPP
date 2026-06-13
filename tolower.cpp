#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

namespace UnixUtils {

    void toLowerCase(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
    }

}

int main() {
    std::string userInput;

    if (!std::getline(std::cin, userInput)) {
        return 0;
    }

    UnixUtils::toLowerCase(userInput);

    std::cout << userInput << "\n";
}
