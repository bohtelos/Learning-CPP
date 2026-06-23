#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

int main() {

    std::vector<int> temperature;
    double temp_f;

    std::ifstream inFile("/sys/class/thermal/thermal_zone0/temp");
    if (!inFile.is_open()) {
        std::cerr << "Error at opening required path.\n";
        return 1;
    }

    std::string line;

    while (std::getline(inFile, line)) {
        temp_f = std::stod(line) / 1000;
        temperature.push_back(temp_f);
    }

    inFile.close();

    std::cout << std::fixed << std::setprecision(1) << temp_f << "℃ \n";

    return 0;
}
