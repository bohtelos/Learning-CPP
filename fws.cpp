#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {

    std::string path = ".";

    if (argc >= 2) {
        path = argv[1];
    }

    uint64_t totalSize = 0;

    for (const auto& p : std::filesystem::recursive_directory_iterator(path)) {
        std::error_code ec;

      uint64_t size = std::filesystem::file_size(p, ec);

      if (!ec) {
          totalSize += size;
    }

    }

    std::cout << "\n---- Folder Weight Stat ----\n";
    std::cout << "Target folder: " << path << "\n";
    std::cout << "Total size: " << totalSize / 1024 / 1024 << "MB\n";

    return 0;

}
