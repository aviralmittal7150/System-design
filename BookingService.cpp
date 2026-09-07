#include "BookingService.h"
#include <iostream>

BookingService::BookingService() = default;

// Encapsulation and Workflow Orchestration
Booking* BookingService::createBooking(const Customer& customer, Show* show, 
                                       const std::vector<std::string>& seatNumbers, 
                                       Payment* payment) {
    if (show == nullptr || payment == nullptr || seatNumbers.empty()) {
        std::cout << "[Error] Invalid booking parameters provided.\n";
        return nullptr;
    }

    // Step 1: Validate seat availability and existence
    std::vector<ShowSeat*> selectedShowSeats;
    for (const auto& seatNum : seatNumbers) {
        ShowSeat* seat = show->findShowSeat(seatNum);
        if (seat == nullptr) {
            std::cout << "[Error] Invalid seat number: " << seatNum << ".\n";
            return nullptr;
        }
        if (!seat->isAvailable()) {
            std::cout << "[Error] Seat " << seatNum << " is already booked.\n";
            return nullptr;
        }
        selectedShowSeats.push_back(seat);
    }

    // Step 2: Calculate total price using PriceCalculator
    std::vector<const ShowSeat*> constSeats(selectedShowSeats.begin(), selectedShowSeats.end());
    double totalAmount = this->priceCalculator.calculatePrice(constSeats);
    std::cout << "\n[Billing] Total Amount for " << selectedShowSeats.size() 
              << " seat(s): ₹" << totalAmount << "\n";

    // Step 3: Process payment via Runtime Polymorphism
    // Runtime Polymorphism: Payment pointer invokes the derived payment implementation at runtime.
    bool paymentSuccess = payment->pay(totalAmount);

    // Step 4: Handle payment result (Rollback & Atomic guarantee)
    if (!paymentSuccess) {
        std::cout << "\n[Booking Status] Payment failed. Booking NOT confirmed. Seats remain AVAILABLE.\n";
        return nullptr;
    }

    // Step 5: Mark selected seats as BOOKED
    for (auto* seat : selectedShowSeats) {
        seat->book();
    }

    // Step 6: Create confirmed Booking record
    auto newBooking = std::make_unique<Booking>(
        customer, show, selectedShowSeats, totalAmount, payment->getPaymentMethodName()
    );

    Booking* bookingPtr = newBooking.get();
    this->bookings.push_back(std::move(newBooking));

    std::cout << "\n[Success] Booking confirmed successfully! Booking ID: " 
              << bookingPtr->getBookingId() << "\n";

    // Step 7: Print ticket using TicketPrinter
    this->ticketPrinter.printTicket(*bookingPtr);

    return bookingPtr;
}

bool BookingService::cancelBooking(const std::string& bookingId) {
    for (auto& booking : this->bookings) {
        if (booking->getBookingId() == bookingId) {
            if (booking->getStatus() == BookingStatus::CANCELLED) {
                std::cout << "[Info] Booking " << bookingId << " is already cancelled.\n";
                return false;
            }
            // Encapsulation: cancel method releases seats and updates status
            booking->cancel();
            std::cout << "\n[Success] Booking " << bookingId << " successfully CANCELLED.\n";
            std::cout << "[Info] All associated seats are now released and AVAILABLE again.\n";
            return true;
        }
    }
    std::cout << "[Error] Booking ID not found: " << bookingId << "\n";
    return false;
}

const Booking* BookingService::findBooking(const std::string& bookingId) const {
    for (const auto& booking : this->bookings) {
        if (booking->getBookingId() == bookingId) {
            return booking.get();
        }
    }
    return nullptr;
}

void BookingService::displayAllBookings() const {
    if (this->bookings.empty()) {
        std::cout << "\nNo bookings found in the system.\n";
        return;
    }

    std::cout << "\n========================================\n";
    std::cout << "ALL SYSTEM BOOKINGS\n";
    std::cout << "========================================\n";
    for (const auto& booking : this->bookings) {
        this->ticketPrinter.printSummary(*booking);
    }
    std::cout << "========================================\n\n";
}

const TicketPrinter& BookingService::getTicketPrinter() const {
    return this->ticketPrinter;
}

const PriceCalculator& BookingService::getPriceCalculator() const {
    return this->priceCalculator;
}
