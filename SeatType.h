#ifndef SEAT_TYPE_H
#define SEAT_TYPE_H

#include <string>

// Enum representing the different tier categories of physical seats
enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

// Helper function to convert SeatType enum to string representation
inline std::string seatTypeToString(SeatType type) {
    switch (type) {
        case SeatType::SILVER:
            return "SILVER";
        case SeatType::GOLD:
            return "GOLD";
        case SeatType::PLATINUM:
            return "PLATINUM";
        default:
            return "UNKNOWN";
    }
}

#endif // SEAT_TYPE_H
