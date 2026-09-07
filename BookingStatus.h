#ifndef BOOKING_STATUS_H
#define BOOKING_STATUS_H

#include <string>

// Enum representing the lifecycle status of a customer booking
enum class BookingStatus {
    CONFIRMED,
    CANCELLED,
    FAILED
};

// Helper function to convert BookingStatus enum to string representation
inline std::string bookingStatusToString(BookingStatus status) {
    switch (status) {
        case BookingStatus::CONFIRMED:
            return "CONFIRMED";
        case BookingStatus::CANCELLED:
            return "CANCELLED";
        case BookingStatus::FAILED:
            return "FAILED";
        default:
            return "UNKNOWN";
    }
}

#endif // BOOKING_STATUS_H
