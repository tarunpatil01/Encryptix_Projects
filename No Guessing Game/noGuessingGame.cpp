#include <iostream>
#include <cstdlib>  // for rand() and RAND_MAX
#include <ctime>    // for time() to seed rand()

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed rand() with current time

    const int Number = rand() % 10 + 1; // Generate random number between 1 and 10
    int guess;
    int attempts = 0;

    std::cout << "Welcome to the Number Guessing Game!\n";
    std::cout << "Guess a number between 1 and 10.\n";

    do {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        attempts++;

        if (guess > Number) {
            std::cout << "Too high! Try again.\n";
        } else if (guess < Number) {
            std::cout << "Too low! Try again.\n";
        } else {
            std::cout << "Congratulations! You guessed the number correctly in "<< attempts <<" attempts.\n";
        }
    } while (guess != Number);

    return 0;
}
