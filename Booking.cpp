#include "Booking.h"

// Static Member Initialization: starts at 1001 for professional ID format (B1001, B1002...)
int Booking::nextBookingId = 1001;

Booking::Booking(const Customer& customer, const Show* show, const std::vector<ShowSeat*>& bookedSeats, 
                 double totalAmount, const std::string& paymentMethod)
    : customer(customer) {
    // Generate unique booking ID using static variable
    this->bookingId = "B" + std::to_string(nextBookingId++);
    this->show = show;
    this->bookedSeats = bookedSeats;
    this->totalAmount = totalAmount;
    this->paymentMethod = paymentMethod;
    // Encapsulation: Initial status is CONFIRMED upon successful instantiation
    this->status = BookingStatus::CONFIRMED;
}

void Booking::resetNextBookingId(int startId) {
    nextBookingId = startId;
}

std::string Booking::getBookingId() const {
    return this->bookingId;
}

const Customer& Booking::getCustomer() const {
    return this->customer;
}

const Show* Booking::getShow() const {
    return this->show;
}

const std::vector<ShowSeat*>& Booking::getBookedSeats() const {
    return this->bookedSeats;
}

double Booking::getTotalAmount() const {
    return this->totalAmount;
}

std::string Booking::getPaymentMethod() const {
    return this->paymentMethod;
}

BookingStatus Booking::getStatus() const {
    return this->status;
}

std::string Booking::getStatusString() const {
    return bookingStatusToString(this->status);
}

// Encapsulation: Controlled method to transition booking state and release seats
bool Booking::cancel() {
    if (this->status == BookingStatus::CONFIRMED) {
        this->status = BookingStatus::CANCELLED;
        for (auto* showSeat : this->bookedSeats) {
            if (showSeat != nullptr) {
                showSeat->release();
            }
        }
        return true;
    }
    return false;
}
