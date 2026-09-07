#include "CinemaApp.h"
#include "UpiPayment.h"
#include "CardPayment.h"
#include "CashPayment.h"
#include <iostream>
#include <sstream>
#include <limits>

CinemaApp::CinemaApp() 
    : cinema("PVR Cinemas, City Center") {
    initializeSampleData();
}

void CinemaApp::initializeSampleData() {
    // 1. Initialize sample movies
    this->movies.emplace_back("Interstellar", "English", 169);
    this->movies.emplace_back("Avengers: Endgame", "English", 181);
    this->movies.emplace_back("Inception", "English", 148);

    // 2. Initialize screens and physical seats (Composition: Screen owns Seats)
    Screen screen1(1);
    Screen screen2(2);

    for (int i = 1; i <= 5; ++i) {
        screen1.addSeat(Seat("A" + std::to_string(i), SeatType::SILVER));
        screen1.addSeat(Seat("B" + std::to_string(i), SeatType::GOLD));
        screen1.addSeat(Seat("C" + std::to_string(i), SeatType::PLATINUM));

        screen2.addSeat(Seat("A" + std::to_string(i), SeatType::SILVER));
        screen2.addSeat(Seat("B" + std::to_string(i), SeatType::GOLD));
        screen2.addSeat(Seat("C" + std::to_string(i), SeatType::PLATINUM));
    }

    this->cinema.addScreen(screen1);
    this->cinema.addScreen(screen2);

    // 3. Initialize shows (Show aggregates Movie & Screen, owns ShowSeats)
    const Screen* sc1 = this->cinema.findScreen(1);
    const Screen* sc2 = this->cinema.findScreen(2);

    this->shows.push_back(std::make_unique<Show>(1, &this->movies[0], sc1, "07:30 PM"));
    this->shows.push_back(std::make_unique<Show>(2, &this->movies[1], sc1, "10:30 PM"));
    this->shows.push_back(std::make_unique<Show>(3, &this->movies[2], sc2, "06:00 PM"));
    this->shows.push_back(std::make_unique<Show>(4, &this->movies[0], sc2, "09:30 PM"));
}

void CinemaApp::showHeader() const {
    std::cout << "\n========================================\n";
    std::cout << "      MOVIE TICKET BOOKING SYSTEM       \n";
    std::cout << "       " << this->cinema.getCinemaName() << "\n";
    std::cout << "========================================\n";
    std::cout << "1. List Movies\n";
    std::cout << "2. View Shows\n";
    std::cout << "3. View Seat Layout\n";
    std::cout << "4. Book Ticket\n";
    std::cout << "5. Print Booking\n";
    std::cout << "6. Cancel Booking\n";
    std::cout << "7. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter your choice (1-7): ";
}

void CinemaApp::handleListMovies() const {
    std::cout << "\n--- CURRENTLY PLAYING MOVIES ---\n";
    for (size_t i = 0; i < this->movies.size(); ++i) {
        std::cout << (i + 1) << ". ";
        this->movies[i].displayInfo();
        std::cout << "\n";
    }
}

void CinemaApp::handleViewShows() const {
    handleListMovies();
    std::cout << "\nEnter movie index (1-" << this->movies.size() << ") to view scheduled shows: ";
    int movieIdx;
    if (!(std::cin >> movieIdx) || movieIdx < 1 || movieIdx > static_cast<int>(this->movies.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Error] Invalid movie selection.\n";
        return;
    }

    const Movie& selectedMovie = this->movies[movieIdx - 1];
    std::cout << "\n--- SHOWS FOR \"" << selectedMovie.getTitle() << "\" ---\n";
    bool found = false;
    for (const auto& show : this->shows) {
        if (show->getMovie()->getTitle() == selectedMovie.getTitle()) {
            show->displayDetails();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No shows currently scheduled for this movie.\n";
    }
}

Show* CinemaApp::selectShowInteractive() {
    std::cout << "\n--- AVAILABLE SHOWS ---\n";
    for (const auto& show : this->shows) {
        show->displayDetails();
    }
    std::cout << "Enter Show ID: ";
    int showId;
    if (!(std::cin >> showId)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return nullptr;
    }
    for (auto& show : this->shows) {
        if (show->getShowId() == showId) {
            return show.get();
        }
    }
    return nullptr;
}

void CinemaApp::handleViewSeatLayout() {
    Show* show = selectShowInteractive();
    if (show == nullptr) {
        std::cout << "[Error] Show not found.\n";
        return;
    }
    show->displaySeatLayout();
}

std::unique_ptr<Payment> CinemaApp::createPaymentFromUserChoice(int choice, double estimatedAmount) {
    if (choice == 1) {
        std::string upiId;
        std::cout << "Enter UPI ID (e.g. user@okhdfcbank or 'fail@upi' to test failure): ";
        std::cin >> upiId;
        return std::make_unique<UpiPayment>(upiId);
    } else if (choice == 2) {
        std::string cardNum, name, cvv;
        std::cout << "Enter Card Number (16 digits): ";
        std::cin >> cardNum;
        std::cout << "Enter Cardholder Name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        std::cout << "Enter CVV (3 digits): ";
        std::cin >> cvv;
        return std::make_unique<CardPayment>(cardNum, name, cvv);
    } else if (choice == 3) {
        double tendered;
        std::cout << "Total amount due: ₹" << estimatedAmount << "\n";
        std::cout << "Enter Cash Tendered: ₹";
        if (!(std::cin >> tendered)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            tendered = 0.0;
        }
        return std::make_unique<CashPayment>(tendered);
    }
    return nullptr;
}

void CinemaApp::handleBookTicket() {
    Show* show = selectShowInteractive();
    if (show == nullptr) {
        std::cout << "[Error] Show not found.\n";
        return;
    }

    show->displaySeatLayout();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string custName, custPhone;
    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, custName);
    std::cout << "Enter Customer Phone: ";
    std::getline(std::cin, custPhone);

    Customer customer(custName, custPhone);

    std::cout << "\nEnter seat numbers separated by spaces (e.g. A1 B2 C3): ";
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::string seatNum;
    std::vector<std::string> seatNumbers;
    while (ss >> seatNum) {
        seatNumbers.push_back(seatNum);
    }

    if (seatNumbers.empty()) {
        std::cout << "[Error] No seat numbers entered.\n";
        return;
    }

    // Pre-calculate estimated amount for user display
    double estimatedTotal = 0.0;
    for (const auto& sNum : seatNumbers) {
        const ShowSeat* ssObj = show->findShowSeat(sNum);
        if (ssObj != nullptr) {
            estimatedTotal += this->bookingService.getPriceCalculator().calculatePrice(ssObj->getSeatType());
        }
    }

    std::cout << "\nChoose Payment Method:\n";
    std::cout << "1. UPI\n";
    std::cout << "2. Card\n";
    std::cout << "3. Cash\n";
    std::cout << "Enter payment option (1-3): ";
    int paymentChoice;
    if (!(std::cin >> paymentChoice) || paymentChoice < 1 || paymentChoice > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[Error] Invalid payment option selected.\n";
        return;
    }

    // Abstraction & Polymorphism: Create Payment-derived object
    std::unique_ptr<Payment> payment = createPaymentFromUserChoice(paymentChoice, estimatedTotal);
    if (payment == nullptr) {
        std::cout << "[Error] Unable to initialize payment method.\n";
        return;
    }

    // Delegate complete booking orchestration to BookingService
    this->bookingService.createBooking(customer, show, seatNumbers, payment.get());
}

void CinemaApp::handlePrintBooking() const {
    std::cout << "\nEnter Booking ID (e.g. B1001) or type 'ALL' to list all bookings: ";
    std::string bookingId;
    std::cin >> bookingId;

    if (bookingId == "ALL" || bookingId == "all") {
        this->bookingService.displayAllBookings();
        return;
    }

    const Booking* booking = this->bookingService.findBooking(bookingId);
    if (booking == nullptr) {
        std::cout << "[Error] No booking found with ID: " << bookingId << "\n";
        return;
    }

    this->bookingService.getTicketPrinter().printTicket(*booking);
}

void CinemaApp::handleCancelBooking() {
    std::cout << "\nEnter Booking ID to cancel (e.g. B1001): ";
    std::string bookingId;
    std::cin >> bookingId;

    this->bookingService.cancelBooking(bookingId);
}

void CinemaApp::run() {
    int choice = 0;
    while (choice != 7) {
        showHeader();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[Error] Invalid choice. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleListMovies();
                break;
            case 2:
                handleViewShows();
                break;
            case 3:
                handleViewSeatLayout();
                break;
            case 4:
                handleBookTicket();
                break;
            case 5:
                handlePrintBooking();
                break;
            case 6:
                handleCancelBooking();
                break;
            case 7:
                std::cout << "\nThank you for using Movie Ticket Booking System. Goodbye!\n";
                break;
            default:
                std::cout << "\n[Error] Invalid choice. Please enter a number between 1 and 7.\n";
                break;
        }
    }
}
