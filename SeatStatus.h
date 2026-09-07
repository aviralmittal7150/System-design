#ifndef SEAT_STATUS_H
#define SEAT_STATUS_H

#include <string>

// Enum representing the booking status of a seat for a specific show
enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

// Helper function to convert SeatStatus enum to string representation
inline std::string seatStatusToString(SeatStatus status) {
    switch (status) {
        case SeatStatus::AVAILABLE:
            return "AVAILABLE";
        case SeatStatus::BOOKED:
            return "BOOKED";
        default:
            return "UNKNOWN";
    }
}

#endif // SEAT_STATUS_H
