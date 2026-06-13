#include <iostream>
#include <string>

int main() {

    std::string task1 = "[ ] Write pseudocode";
    std::string task2 = "[ ] Fix bug in Kate";
    std::string task3 = "[ ] Configure Arch Linux";

    std::string* currentTask = nullptr;

    int choice;
    std::cout << "Select a task (1-3): ";
    std::cin >> choice;

    if (choice == 1) {

        currentTask = &task1;
    }

    else if (choice == 2) {

        currentTask = &task2;
    }

    else if (choice == 3) {

        currentTask = &task3;
    }

    else {

        std::cout << "Invalid choice!\n";
        return 1;
    }

    std::cout << "Task loaded at memory adress of: " << currentTask << "\n";
    std::cout << "Task content: " << *currentTask << "\n";

    return 0;

}
