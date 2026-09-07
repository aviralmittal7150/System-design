#include "Seat.h"

// Constructor demonstrating 'this' pointer usage
Seat::Seat(const std::string& seatNumber, SeatType seatType) {
    // 'this' pointer clearly distinguishes member variables from constructor parameters
    this->seatNumber = seatNumber;
    this->seatType = seatType;
}

// Encapsulation: Controlled getter for seat number
std::string Seat::getSeatNumber() const {
    return this->seatNumber;
}

// Encapsulation: Controlled getter for seat type
SeatType Seat::getSeatType() const {
    return this->seatType;
}

std::string Seat::getSeatTypeString() const {
    return seatTypeToString(this->seatType);
}
