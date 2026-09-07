#include "ShowSeat.h"

// Constructor initializes ShowSeat with AVAILABLE status and references the physical seat
ShowSeat::ShowSeat(const Seat* physicalSeat) {
    this->physicalSeat = physicalSeat;
    // Encapsulation: Default status set internally to AVAILABLE
    this->status = SeatStatus::AVAILABLE;
}

const Seat* ShowSeat::getPhysicalSeat() const {
    return this->physicalSeat;
}

std::string ShowSeat::getSeatNumber() const {
    return this->physicalSeat ? this->physicalSeat->getSeatNumber() : "";
}

SeatType ShowSeat::getSeatType() const {
    return this->physicalSeat ? this->physicalSeat->getSeatType() : SeatType::SILVER;
}

std::string ShowSeat::getSeatTypeString() const {
    return this->physicalSeat ? this->physicalSeat->getSeatTypeString() : "";
}

SeatStatus ShowSeat::getStatus() const {
    return this->status;
}

std::string ShowSeat::getStatusString() const {
    return seatStatusToString(this->status);
}

bool ShowSeat::isAvailable() const {
    return this->status == SeatStatus::AVAILABLE;
}

// Encapsulation: seat status is private and modified through controlled methods.
bool ShowSeat::book() {
    if (this->status == SeatStatus::AVAILABLE) {
        this->status = SeatStatus::BOOKED;
        return true;
    }
    return false;
}

// Encapsulation: seat status is private and modified through controlled methods.
void ShowSeat::release() {
    this->status = SeatStatus::AVAILABLE;
}
