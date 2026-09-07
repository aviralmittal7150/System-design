#include "Screen.h"

Screen::Screen(int screenNumber) {
    this->screenNumber = screenNumber;
}

int Screen::getScreenNumber() const {
    return this->screenNumber;
}

std::string Screen::getScreenName() const {
    return "Screen " + std::to_string(this->screenNumber);
}

// Composition: Screen populates its owned collection of Seat objects
void Screen::addSeat(const Seat& seat) {
    this->seats.push_back(seat);
}

const std::vector<Seat>& Screen::getSeats() const {
    return this->seats;
}

const Seat* Screen::findSeat(const std::string& seatNumber) const {
    for (const auto& s : this->seats) {
        if (s.getSeatNumber() == seatNumber) {
            return &s;
        }
    }
    return nullptr;
}
