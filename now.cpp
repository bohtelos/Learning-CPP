#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

// Global

int hour = 0;
int minute = 0;
int second = 0;

std::atomic<bool> count = true;

void padZero(int h, int m, int s) {
    
    if (h < 10) {
    
    std::cout << "Hour: " << "0" << h << " ";
    
    } else {
    
    std::cout << "Hour: " << h << " ";
    
    }
    
    if (m < 10) {
    
    std::cout << "Minute: " << "0" << m << " ";
    
    } else {
    
    std::cout << "Minute: " << m << " ";
    
    }
    
    if (s < 10) {
    
    std::cout << "Second: " << "0" << s;
    
    } else {
    
    std::cout << "Second: " << s;
    
    }
    
    std::cout << std::flush;

}

void clock_run() {

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
        
        padZero(hour, minute, second);

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
