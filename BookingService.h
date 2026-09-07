#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include <vector>
#include <memory>
#include <string>
#include "Customer.h"
#include "Show.h"
#include "Booking.h"
#include "Payment.h"
#include "PriceCalculator.h"
#include "TicketPrinter.h"

// Service Class: BookingService
// Single Responsibility Principle (SRP): Orchestrates the complete booking and cancellation workflow.
// Dependency Inversion Principle (DIP): Depends on abstract Payment interface (Payment*) rather than concrete payment types.
// Association with Customer: Customer interacts with BookingService to book tickets without lifetime dependency.
class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    // Aggregation/Management of Booking objects
    std::vector<std::unique_ptr<Booking>> bookings;

public:
    BookingService();
    ~BookingService() = default;

    // Orchestrates the booking workflow
    // Runtime Polymorphism: Payment* can point to UpiPayment, CardPayment, or CashPayment
    Booking* createBooking(const Customer& customer, Show* show, 
                           const std::vector<std::string>& seatNumbers, 
                           Payment* payment);

    // Cancel an existing booking by booking ID
    bool cancelBooking(const std::string& bookingId);

    // Find a booking by its unique ID
    const Booking* findBooking(const std::string& bookingId) const;

    // List all bookings
    void displayAllBookings() const;

    const TicketPrinter& getTicketPrinter() const;
    const PriceCalculator& getPriceCalculator() const;
};

#endif // BOOKING_SERVICE_H
