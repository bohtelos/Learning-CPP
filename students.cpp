#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <string>
#include <vector>

struct Student {
  int id;
  std::string name;
  std::vector<int> grades;
};

int main() {

  std::vector<Student> students;
  bool keepGoing = true;
  int nextStudentID = 1;

  while (keepGoing) {

    std::cout << "\n---- Student Grade System ----\n";
    std::cout << "1 - Add Student\n";
    std::cout << "2 - Add Grade to Student\n";
    std::cout << "3 - View All Students and Grades\n";
    std::cout << "4 - Find Top Students\n";
    std::cout << "5 - Exit\n";
    std::cout << "Enter your choice: \n";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (std::cin.fail()) {

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid Input! Please enter a number.\n";
      continue;
      
    }

    if (choice == 1) {

    }

    else if (choice == 2) {

    }

    else if (choice == 3) {

    }

    else if (choice == 4) {

    }

    else if (choice == 5) {

      keepGoing = false;
      std::cout << "Exiting program. Goodbye!\n";
    }

    else {

      std::cout << "Wrong input! Please try again.\n";
    }
    
  }
  
  return 0;
}
