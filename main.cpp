#include "CinemaApp.h"
#include <iostream>

// Main entry point for the Movie Ticket Booking System
int main() {
    try {
        CinemaApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
