#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>

struct Product {

    std::string name;
    int quantity;
    double price;

};

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << "input_file <output_file>\n";
        return 1;
    }

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    std::ifstream file (input_filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << input_filename << "\n";
        return 1;
    }

    std::string line;
    std::vector<Product> products;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, qty_str, price_str;

        std::getline(ss, name, '|');
        std::getline(ss, qty_str, '|');
        std::getline(ss, price_str, '|');

        Product p;
        p.name = name;

        try {

        p.quantity = std::stoi(qty_str);
        p.price = std::stod(price_str);

        }

        catch (const std::invalid_argument& e) {
            std::cerr << "Error: Wrong format of data in line: " << line << "\n";
            continue;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Error: Number too big in line: " << line << "\n";
            continue;
        }

        products.push_back(p);

        std::cout << "Products read: " << products.size() << "\n";
        for (const auto& item : products) {
            std::cout << "Product: " << item.name << " | quantity: " << item.quantity << " | price: " << item.price << "\n";
        }

    }

    std::ofstream out_file(output_filename);
    if (!out_file.is_open()) {
        std::cerr << "Error: Could not create file: " << output_filename << "\n";
        return 1;
    }

    for (const auto& item : products) {

        double total_price = item.quantity * item.price;

        std::cout << "Product: " << item.name << " | Total price: "<< total_price << "\n";

        out_file << item.name << " | " << item.quantity << " | " << item.price << " | Total price: " << total_price << "\n";
    }

    try {
        std::filesystem::rename(input_filename, output_filename);
        std::cout << "File " << input_filename << " was renamed to " << output_filename << " successfully.\n";
    }

    catch (const std::filesystem::filesystem_error& e) {

        std::cerr << "Renaming error: " << e.what() << "\n";

    }

    std::cout << "Successfully converted " << products.size() << " products to " << output_filename << "\n";

    return 0;
}
