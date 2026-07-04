#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// Global

std::atomic<bool> count = true;

void clock_run() {

    // Initialize

    int hour = 0;
    int minute = 0;
    int second = 0;

    // Loop and update

    while (count) {

        system("clear");

        second++;

        if (second == 60) {
            second = 0;
            minute++;
        }

        if (minute == 60) {
            minute = 0;
            hour++;
        }

        if (hour == 24) {
            hour = 0;
        }

        // See out

        std::cout << "Hour: " << hour << "\n";
        std::cout << "Minute: " << minute << "\n";
        std::cout << "Second: " << second << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

}

int main() {

    // Manipulation

    std::thread t(clock_run);
    std::cin.get();
    count = false;
    t.join();

    // End

    return 0;

}
