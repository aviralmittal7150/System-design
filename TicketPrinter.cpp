#include "TicketPrinter.h"
#include <iomanip>

// Compile-Time Polymorphism (Overload 1)
void TicketPrinter::printTicket(const Booking& booking) const {
    printTicket(booking, std::cout);
}

// Compile-Time Polymorphism (Overload 2)
void TicketPrinter::printTicket(const Booking& booking, std::ostream& out) const {
    const Show* show = booking.getShow();
    const Movie* movie = show ? show->getMovie() : nullptr;
    const Screen* screen = show ? show->getScreen() : nullptr;

    out << "\n========================================\n";
    out << "TICKET\n";
    out << "======\n\n";
    out << "Booking ID : " << booking.getBookingId() << "\n";
    out << "Customer   : " << booking.getCustomer().getName() << " (" << booking.getCustomer().getPhone() << ")\n";
    out << "Movie      : " << (movie ? movie->getTitle() : "N/A") << "\n";
    out << "Screen     : " << (screen ? screen->getScreenName() : "N/A") << "\n";
    out << "Time       : " << (show ? show->getStartTime() : "N/A") << "\n\n";

    out << "Seats:\n";
    for (const auto* showSeat : booking.getBookedSeats()) {
        if (showSeat != nullptr) {
            out << showSeat->getSeatNumber() << " - " << showSeat->getSeatTypeString() << "\n";
        }
    }

    out << "\nTotal Amount : ₹" << std::fixed << std::setprecision(2) << booking.getTotalAmount() << "\n\n";
    out << "Payment      : " << booking.getPaymentMethod() << "\n";
    out << "Status       : " << booking.getStatusString() << "\n\n";
    out << "========================================\n\n";
}

// Compile-Time Polymorphism (Overload 3)
void TicketPrinter::printSummary(const Booking& booking) const {
    std::cout << "[Ticket Summary] ID: " << booking.getBookingId()
              << " | Customer: " << booking.getCustomer().getName()
              << " | Amount: ₹" << booking.getTotalAmount()
              << " | Status: " << booking.getStatusString() << "\n";
}
