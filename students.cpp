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

  std::ifstream inFile("students.txt");

  if (inFile.is_open()) {

    int id;
    std::string name;
    int gradesCount;

    while (inFile >> id >> name >> gradesCount) {

      Student tempStudent;
      tempStudent.id = id;
      tempStudent.name = name;

      for (int i = 0; i < gradesCount; ++i) {

	int grade;
	inFile >> grade;
	tempStudent.grades.push_back(grade);

      }

      students.push_back(tempStudent);
      
    }

    if (!students.empty()) {

      nextStudentID = students.back().id + 1;

    }

    inFile.close();

  }

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

      std::cout << "Enter a name: \n";
      std::string name;
      std::getline(std::cin, name);

      while (name.empty()) {

	std::cout << "Name cannot be empty\n";
	std::cout << "Enter a name: \n";
	std::getline(std::cin, name);
	
      }

      Student tempStudent;
      tempStudent.id = nextStudentID;
      tempStudent.name = name;

      students.push_back(tempStudent);
      nextStudentID++;
      
    }

    else if (choice == 2) {

      std::cout << "Enter student ID to add a grade: \n";
      int studentID;
      std::cin >> studentID;

      while (std::cin.fail() || studentID <= 0) {

	std::cout << "Invalid ID! Enter a valid positive number: \n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> studentID;

      }

      std::cin.ignore();

      int foundIndex = -1;

      for (int i = 0; i < students.size(); i++) {

	if (students[i].id == studentID) {

	  foundIndex = i;
	  break;

	}

      }

      if (foundIndex == -1) {

	std::cout << "Student with this ID is not found, nor exists.\n";

      }

      else {

	std::cout << "Student found: " << students[foundIndex].name << "\n";

	std::cout << "Enter a grade (1 - 12): \n";
	int grade;
	std::cin >> grade;

	while (std::cin.fail() || grade < 1 || grade > 12) {

	  std::cout << "Invalid grade! Enter a number between 1 and 12: \n";
	  std::cin.clear();
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  std::cin >> grade;

	}

	std::cin.ignore();
	students[foundIndex].grades.push_back(grade);
	std::cout << "Grade added successfully!\n";

      }
      
    }

    else if (choice == 3) {

      if (students.empty()) {

	std::cout << "No students in the database yet.\n";
	
      }

      else {

	std::cout << "\n---- All Students & Grades ----\n";

	for (const Student& student : students) {

	  std::cout << "ID: " << student.id << " |  Name: " << student.name << " | Grades: ";

	  double sum = 0.0;

	  for (int grade : student.grades) {

	    std::cout << grade << " ";

	    sum += grade;

	  }

	  if (student.grades.empty()) {

	    std::cout << " | Average: No grades yet";
	    
	  }

	  else {

	    double average = sum / student.grades.size();
	    std::cout << " | Average: " << average;

	  }

	  std::cout << "\n";

	}
	
      }

    }

    else if (choice == 4) {

      if (students.empty()) {

	std::cout << "No students in the database yet.\n";

      }

      else {
	double maxAverage = -1.0;

	for (const Student& student : students) {

	  if (student.grades.empty()) {
	    continue;
	  }

	  double sum = 0.0;
	  for (int grade : student.grades) {
	    sum += grade;

	  }

	  double average = sum / student.grades.size();
	  if (average > maxAverage) {
	    maxAverage = average;

	  }

	}

	if (maxAverage == -1.0) {
	  std::cout << "No grades have been added to any students yet.\n";
	}

	else {
	  std::cout << "\n---- Top Student(s) (Max Average: " << maxAverage << ") ----\n";

	  for (const Student& student : students) {

	    if (student.grades.empty()) {
	      continue;
	    }

	    double sum = 0.0;
	    for (int grade : student.grades) {

	      sum += grade;
	    }

	    double average = sum / student.grades.size();

	    if (average == maxAverage) {

	      std::cout << "ID: " << student.id << " | Name: " << student.name << "\n";
	      
	    }

	  }
	  
	}

      }

    }

    else if (choice == 5) {

      std::ofstream outFile("students.txt");

      if (!outFile) {

	std::cout << "Error: Could not save data to file.\n";

      }

      else {

	for (const Student& student : students) {

	  outFile << student.id << " " << student.name << " " << student.grades.size() << " ";

	  for (int grade : student.grades) {

	    outFile << grade  << " ";

	  }

	  outFile << "\n";

	}

	outFile.close();
	std::cout << "Data successfully saved to students.txt\n";

      }

      keepGoing = false;
      std::cout << "Exiting program. Goodbye!\n";
    }

    else {

      std::cout << "Wrong input! Please try again.\n";
    }
    
  }
  
  return 0;
}
