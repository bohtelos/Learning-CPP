#include <iostream>
#include <filesystem>
#include <string>
#include <cstdio>
#include <string_view>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Error: Invalid number of arguments.\n";
        std::cerr << "Usage: " << argv[0] << " <old_name> <new_name>\n";
        return 1;
    }

    bool interactive = false;
    bool verbose = false;
    bool force = false;

    argv++;

    while (*argv != nullptr && std::string_view(*argv).starts_with('-')) {
        std::string_view flag(*argv);

        if (flag == "-i") {
            interactive = true;
        }

        else if (flag == "-v") {
            verbose = true;
        }

        else if (flag == "-f") {
            force = true;
        }

        else {
            std::cerr << "Unknown flag: " << flag << "\n";
            return 1;
        }

        argv++;

    }

    const char* currentName = *argv;

    argv++;

    const char* newName = *argv;

    if (currentName == nullptr || newName == nullptr) {
        std::cerr << "Error: Missing file name(s).\n";
        return 1;
    }

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

    if (std::filesystem::exists(newName) && !force) {
        std::cerr << "Error: The file '" << newName << "' already exists. Use -f to overwrite.\n";
        return 1;
    }

    if (verbose) {

        if (std::filesystem::exists(newName)) {

        std::cout << "[VERBOSE] Overwriting an existing file '" << newName << "'\n";

        }

        std::cout << "Renaming '" << currentName << "' to '" << newName << "'\n";

    }

    if (std::rename(currentName, newName) != 0) {
        std::cerr << "Error: Could not rename the file. Make sure it exists.\n";
        return 1;
    }

    if (force) {

    }

    return 0;

}
