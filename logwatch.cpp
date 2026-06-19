#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <string_view>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Usage: ./logwatch <file_path>\n";
        return 1;
    }

    std::filesystem::path filePath = argv[1];

    std::streampos lastPos = std::filesystem::exists(filePath) ? std::filesystem::file_size(filePath) : 0;

    while (true) {

        try {

        if (!std::filesystem::exists(filePath)) {
            std::cerr << "Path not found.\n";
            return 1;
        }

        std::ifstream logFile(filePath);
        if (!logFile.is_open()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        logFile.seekg(lastPos);

        std::uintmax_t currentSize = std::filesystem::file_size(filePath);

        if (currentSize > lastPos) {
            logFile.clear();
            logFile.seekg(lastPos);

            std::string line;
            while (std::getline(logFile, line)) {

                if (line.find("ERROR") != std::string::npos) {

                std::cout << "\033[31m" << line << "\033[0m" << "\n";
            }
            else {
                std::cout << line << "\n";
            }
                }
            lastPos = logFile.tellg();
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        }

        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "\033[31m[ERROR] System failure: " << e.what() << "\033[0m" << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

    }

    return 0;

}
