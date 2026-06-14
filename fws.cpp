#include <iostream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>

struct FileInfo {
    std::string path;
    uint64_t size;
};

bool compareFiles(const FileInfo& a, const FileInfo& b) {
    return a.size > b.size;
}

std::string formatSize(uint64_t bytes) {
    std::vector<std::string> units = {"B", "KB", "MB", "GB", "TB"};

    double size = bytes;
    size_t unitIndex = 0;

    while (size >= 1024 && unitIndex < units.size() - 1) {
        size /= 1024.0;
        unitIndex++;
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << size << " " << units[unitIndex];
    return stream.str();

}

int main(int argc, char* argv[]) {

    std::string path = ".";

    if (argc >= 2) {
        path = argv[1];
    }

    uint64_t totalSize = 0;

    std::vector<FileInfo> fileList;

    for (const auto& p : std::filesystem::recursive_directory_iterator(path)) {
        std::error_code ec;

      uint64_t size = std::filesystem::file_size(p, ec);

      if (!ec) {
          totalSize += size;

          FileInfo info;

          info.path = p.path().string();
          info.size = size;

          fileList.push_back(info);
    }

    }

    std::sort(fileList.begin(), fileList.end(), compareFiles);

    std::cout << "\n---- Top 10 largest files ----\n";

    for (size_t i = 0; i < 10 && i < fileList.size(); ++i) {
        std::cout << i + 1 << ". " << fileList[i].path << " (" << formatSize(fileList[i].size) << ")\n";
    }

    std::cout << "\n---- Folder Weight Stat ----\n";
    std::cout << "Target folder: " << path << "\n";
    std::cout << "Total size: " << formatSize(totalSize) << "\n";

    return 0;

}
