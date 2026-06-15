#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <chrono>

int main() {

    while (true) {

    std::ifstream memFile("/proc/meminfo");

    if (!memFile.is_open()) {
        std::cerr << "Error: Could not open /proc/meminfo\n";
        return 1;
    }

    std::string line;
    uint64_t totalMem = 0;
    uint64_t avaibleMem = 0;
    std::cout << "Reading /proc/meminfo...\n";

    while (std::getline(memFile, line)) {

    if (line.find("MemTotal:") != std::string::npos) {
        std::stringstream ss(line);
        std::string trash;
        ss >> trash >> totalMem;
    }

    if (line.find("MemAvailable:") != std::string::npos) {
        std::stringstream ss(line);
        std::string trash;
        ss >> trash >> avaibleMem;
    }

    }

    memFile.close();

    if (totalMem == 0) {
        std::cerr << "Error: Could not read memory info.\n";
        return 1;
    }

    uint64_t usedMem = totalMem - avaibleMem;
    double usedPercentage = (static_cast<double>(usedMem) / totalMem) * 100.0;

    std::ifstream cpuFile("/proc/loadavg");
    if (!cpuFile.is_open()) {
        std::cerr << "Error: Could not open /proc/loadavg\n";
        return 1;
    }

    double lavg1 = 0.0, lavg5 = 0.0, lavg15 = 0.0;
    std::string cpuLine;

    if (std::getline(cpuFile, cpuLine)) {
        std::stringstream ss(cpuLine);
        ss >> lavg1 >> lavg5 >> lavg15;
    }

    cpuFile.close();

    std::system("clear");

    std::cout << "\n Press Ctrl + C to exit.\n";

    std::cout << "\n---- RAM Monitor ----\n";
    std::cout << "Total memory: " << totalMem / 1024 << " MB\n";
    std::cout << "Used memory: " << usedMem / 1024 << " MB\n";
    std::cout << "Avaible memory: " << avaibleMem / 1024 << " MB\n";

    std::cout << "Memory usage: " << std::fixed << std::setprecision(1) << usedPercentage << "%\n";

    std::cout << "\n---- CPU Load Average ----\n";
    std::cout << "Last 1 min: " << std::fixed << std::setprecision(2) << lavg1 << "\n";
    std::cout << "Last 5 min: " << lavg5 << "\n";
    std::cout << "Last 15 min: " << lavg15 << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));

    }

    return 0;

}
