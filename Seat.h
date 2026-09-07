#ifndef SEAT_H
#define SEAT_H

#include <string>
#include "SeatType.h"

// Entity Class: Seat
// Single Responsibility: Represents a single physical seat within a screen/auditorium.
// Must NOT know about bookings or payments.
class Seat {
private:
    // Encapsulation: Seat attributes are kept private
    std::string seatNumber;
    SeatType seatType;

public:
    Seat(const std::string& seatNumber, SeatType seatType);

    std::string getSeatNumber() const;
    SeatType getSeatType() const;
    std::string getSeatTypeString() const;
};

#endif // SEAT_H
