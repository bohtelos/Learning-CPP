#include <iostream>
#include <vector>
#include <fstream>
#include <string>

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

    std::cout << "\n---- List of my tasks ----\n";
    for (size_t i = 0; i < todoList.size(); ++i) {

        if (todoList[i].isDone) {
            std::cout << "[X] ";
        }
        else {
            std::cout << "[] ";
        }

        std::cout << todoList[i].text << "\n";

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
