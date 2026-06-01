#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>

struct Task {
    std::string text;
    bool isDone;
};

int main() {


    std::cout << "A todo tool by bohtelos\n";

    std::vector<Task> todoList;

    std::ifstream inFile("todo.txt");
    if (inFile.is_open()) {
        int status;
        std::string taskText;

        while (inFile >> status) {
            inFile.ignore();
            std::getline(inFile, taskText);

            Task tempTask;
            tempTask.text = taskText;
            tempTask.isDone = (status == 1);

            todoList.push_back(tempTask);

        }
        inFile.close();
    }

    int taskNumber;
    bool keepGoing = true;

    while (keepGoing == true) {
    std::cout << "\n---- List of my tasks ----\n";
    for (size_t i = 0; i < todoList.size(); ++i) {

        if (todoList[i].isDone) {
            std::cout << "[X] ";
        }
        else {
            std::cout << "[] ";
        }

        std::cout << i << ". " << todoList[i].text << "\n";
    }

        std::cout << "What would you like to do?\n";
        std::cout << "1 - Mark task as done\n";
        std::cout << "2 - Delete a task\n";
        std::cout << "3 - Add a new task\n";
        std::cout << "4 - Exit\n";

        int choice;
        bool validOption = false;
        bool validTaskNumber = false;

        while (!validOption) {

        std::cout << "Enter your option: \n";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
        }
        else {
            validOption = true;
        }

        }

        if (choice == 1) {
            validTaskNumber = false;
            std::cout << "\nWhich task do you want to mark as done?\n";

            while (!validTaskNumber) {

            std::cin >> taskNumber;
            std::cin.ignore();

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wrong input.\n";
            }

            else if (taskNumber < 0 || taskNumber >= todoList.size()) {
                std::cout << "Wrong input.\n";
            }

            else {
                validTaskNumber = true;
                todoList[taskNumber].isDone = true;
                std::cout << "Task marked as done!\n";
            }

        }
        }

        else if (choice == 2) {
            std::cout << "Which task do you want to delete?\n";

            while (!validTaskNumber) {
                std::cout << "Enter task number: \n";
                std::cin >> taskNumber;
                std::cin.ignore();

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Wrong input.\n";
                }

                else if (taskNumber < 0 || taskNumber >= todoList.size()) {
                    std::cout << "Task out of range.\n";
                }

                else {
                    validTaskNumber = true;
                    todoList.erase(todoList.begin() + taskNumber);
                    std::cout << "Task deleted!\n";
                }

            }
        }

        else if (choice == 3) {
            std::cout << "Enter new task: \n";
            std::string newText;
            std::getline(std::cin, newText);

            if (!newText.empty()) {
                Task newTask;
                newTask.text = newText;
                newTask.isDone = false;
                todoList.push_back(newTask);
                std::cout << "Task added successfully.\n";
            }
            else {
                std::cout << "Empty task not added.\n";
            }
        }

        else if (choice == 4) {
            keepGoing = false;
        }

        else {
            std::cout << "Invalid input.\n";
        }

    }


    std::ofstream outFile("todo.txt");
    if (outFile.is_open()) {
        for (const Task& task : todoList) {
            outFile << (task.isDone ? 1 : 0) << " " << task.text << "\n";
        }
        outFile.close();
        std::cout << "Changes saved to the file.\n";
    }

    return 0;
}
