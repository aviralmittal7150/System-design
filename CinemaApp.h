#ifndef CINEMA_APP_H
#define CINEMA_APP_H

#include <vector>
#include <memory>
#include "Cinema.h"
#include "Movie.h"
#include "Show.h"
#include "BookingService.h"

// UI / Orchestrator Class: CinemaApp
// Responsibility: Handles user interface, console menus, user input reading, and connects UI to BookingService.
// Keeps UI logic separate from core domain and business logic.
class CinemaApp {
private:
    Cinema cinema;
    std::vector<Movie> movies;
    std::vector<std::unique_ptr<Show>> shows;
    BookingService bookingService;

    void initializeSampleData();
    void showHeader() const;
    void handleListMovies() const;
    void handleViewShows() const;
    void handleViewSeatLayout();
    void handleBookTicket();
    void handlePrintBooking() const;
    void handleCancelBooking();

    // Helper input handlers
    std::unique_ptr<Payment> createPaymentFromUserChoice(int choice, double estimatedAmount);
    Show* selectShowInteractive();

public:
    CinemaApp();
    void run();
};

#endif // CINEMA_APP_H
