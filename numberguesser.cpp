#include <iostream>
#include <random>

int main() {

    std::random_device rd;
    std::mt19937 gen (rd());

    std::uniform_int_distribution<> distrib(1, 100);

    int secretNumber = distrib(gen);
    int attempts = 0;
    int userGuess = 0;

    std::cout << "---- Number guessing game----\n";
    std::cout << "There is a guessed number from 1 to 100. Try guessing it\n";

    while (userGuess != secretNumber) {
        std::cout << "Enter the number: ";
        std::cin >> userGuess;
        attempts++;

        if (userGuess > secretNumber) {
            std::cout << "Your number is higher than the number\n";
        }

        else if (userGuess < secretNumber) {
            std::cout << "Your number is lower than the number\n";
        }

        else {
            std::cout << "You guessed the number! Well done!\n";
            std::cout << "To guess the number, it took you " << attempts << " attempts\n";
        }

    }

    return 0;

}
