#include <iostream>
#include <filesystem>
#include <string>
#include <cstdio>
#include <string_view>

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 4) {
        std::cerr << "Error: Invalid number of arguments.\n";
        std::cerr << "Usage: " << argv[0] << " <old_name> <new_name>\n";
        return 1;
    }

    bool interactive = false;

    argv++;

    if (std::string_view(*argv) == "-i") {
        interactive = true;
        argv++;
    }

    const char* currentName = *argv;

    argv++;

    const char* newName = *argv;

    if (!std::filesystem::exists(currentName)) {
        std::cerr << "Error: The file '" << currentName << "' does not exist. Renaming canceled.\n";
        return 1;
    }


    if (interactive) {
        std::cout << "Are you sure you want to rename '" << currentName << "' to '" << newName << "'?(y/n): ";
        char answer;
        std::cin >> answer;

        if (answer != 'y' && answer != 'Y') {
            std::cout << "Operation cancelled by user.\n";
            return 0;
        }

    }

    if (std::rename(currentName, newName) != 0) {
        std::cerr << "Error: Could not rename the file. Make sure it exists.\n";
        return 1;
    }

    return 0;

}
