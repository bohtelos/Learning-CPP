#include <iostream>
#include <random>
#include <limits>
#include <cctype>
#include <vector>
#include <algorithm>
#include <fstream>

void printHighScores(std::vector<int>& scores) {
    std::sort(scores.begin(), scores.end());

    std::cout << "\n---- Best attempts ----\n";
    for (int score : scores) {
        std::cout << score << " attempts\n";
    }

}

int getDifficulty() {
    int choice;

    std::cout << "\n---- Choose difficulty----\n";
    std::cout << "1. Easy: Unlimited attempts\n";
    std::cout << "2. Medium: 7 attempts\n";
    std::cout << "3. Hard: 5 attempts\n";
    std::cout << "Your choice: ";

    while (!(std::cin >> choice) || choice < 1 || choice > 3) {

        std::cout << "\nWrong choice! Enter 1, 2, or 3: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }

    return choice;

}

int main() {

    int minNum = 1;
    int maxNum = 100;
    int maxAttempts = 0;
    char playAgain;

    std::vector<int> highScores;
    highScores.reserve(20);

    std::ifstream inFile("scores.txt");
    if (inFile.is_open()) {
        int score;
        while (inFile >> score) {
            highScores.push_back(score);
        }
        inFile.close();
    }

    do {

    int difficulty = getDifficulty();

    if (difficulty == 1) {
        maxAttempts = 0;
        maxNum = 50;
        std::cout << "\nEasy difficulty chosen: there is a number guessed from 1 to 50\n";
    }

    else if (difficulty == 2) {
        maxAttempts = 7;
        maxNum = 100;
        std::cout << "\nMedium difficulty chosen: there is a number guessed from 1 to 100\n";
    }

    else if (difficulty == 3) {
        maxAttempts = 5;
        maxNum = 200;
        std::cout << "\nHard difficulty chosen: there is a number guessed from 1 to 200\n";
    }

    std::random_device rd;
    std::mt19937 gen (rd());

    std::uniform_int_distribution<> distrib(minNum, maxNum);

    int secretNumber = distrib(gen);
    int attempts = 0;
    int userGuess = 0;
    int remainingAttempts = maxAttempts;

    std::cout << "---- Number guessing game----\n";

    while (userGuess != secretNumber) {
        std::cout << "Enter the number: ";
        if (!(std::cin >> userGuess)) {

            std::cout << "Wrong input! Try again!\n";

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;

        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        attempts++;

        if (maxAttempts > 0) {
            remainingAttempts--;

            std::cout << "\nRemaining attempts: " << remainingAttempts << "\n";

        }


        if (userGuess > secretNumber) {
            std::cout << "Your number is higher than the number\n";
        }

        else if (userGuess < secretNumber) {
            std::cout << "Your number is lower than the number\n";
        }

        else {
            std::cout << "You guessed the number! Well done!\n";
            std::cout << "To guess the number, it took you " << attempts << " attempts\n";

            highScores.push_back(attempts);

            printHighScores(highScores);

            break;
        }

        if (maxAttempts > 0 && remainingAttempts == 0) {
            std::cout << "\nSorry, but you ran out of attempts\n";
            std::cout << "\nThe secret number was: " << secretNumber << "\n";
            break;
        }

    }


    std::cout << "\nWould you like to play again? (y/n): ";
    std::cin >> playAgain;
    playAgain = std::tolower(playAgain);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (playAgain == 'y');

    std::ofstream outFile("scores.txt");
    if (outFile.is_open()) {
        for (int score : highScores) {
            outFile << score << "\n";
        }

        outFile.close();
    }

    std::cout << "\nThank you for playing the game! Goodbye!\n";

    return 0;

}
