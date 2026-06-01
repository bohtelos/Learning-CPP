#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>

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

        std::cout << "\nEnter task number to mark as done or -1 to skip: ";
        std::cin >> taskNumber;
        std::cin.ignore();

        if (taskNumber == -1) {
            std::cout << "Skipping...\n";
        }

        else if (taskNumber < 0 || taskNumber >= todoList.size()) {
            std::cout << "\nWrong input!\n";
        }
        else {

            todoList[taskNumber].isDone = true;
            std::cout << "Task marked as done!\n";
        }

        std::cout << "\nDo you want to add new task? (Or press ENTER to leave): \n";
        std::string newText;
        std::getline(std::cin, newText);

        if (!newText.empty()) {
            Task newTask;
            newTask.text = newText;
            newTask.isDone = false;

            todoList.push_back(newTask);
            std::cout << "\nNew task has been added to the list.\n";

        }

        std::cout << "\nDo you want to continue? (y/n): ";
        char answer;
        std::cin >> answer;
        answer = std::tolower(answer);

        switch (answer) {
            case 'y':
                keepGoing = true;
                break;
            case 'n':
                keepGoing = false;
                break;
            default:
                std::cout << "\nWrong command.\n";
                break;

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
