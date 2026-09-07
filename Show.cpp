#include "Show.h"
#include <iostream>
#include <iomanip>

Show::Show(int showId, const Movie* movie, const Screen* screen, const std::string& startTime) {
    this->showId = showId;
    this->movie = movie;
    this->screen = screen;
    this->startTime = startTime;

    // Composition: Initialize ShowSeat collection from the physical seats of the assigned Screen
    if (this->screen != nullptr) {
        for (const auto& seat : this->screen->getSeats()) {
            this->showSeats.emplace_back(&seat);
        }
    }
}

int Show::getShowId() const {
    return this->showId;
}

const Movie* Show::getMovie() const {
    return this->movie;
}

const Screen* Show::getScreen() const {
    return this->screen;
}

std::string Show::getStartTime() const {
    return this->startTime;
}

const std::vector<ShowSeat>& Show::getShowSeats() const {
    return this->showSeats;
}

std::vector<ShowSeat>& Show::getShowSeats() {
    return this->showSeats;
}

ShowSeat* Show::findShowSeat(const std::string& seatNumber) {
    for (auto& ss : this->showSeats) {
        if (ss.getSeatNumber() == seatNumber) {
            return &ss;
        }
    }
    return nullptr;
}

const ShowSeat* Show::findShowSeat(const std::string& seatNumber) const {
    for (const auto& ss : this->showSeats) {
        if (ss.getSeatNumber() == seatNumber) {
            return &ss;
        }
    }
    return nullptr;
}

void Show::displayDetails() const {
    std::cout << "Show ID: " << this->showId 
              << " | Movie: " << (this->movie ? this->movie->getTitle() : "N/A")
              << " | Screen: " << (this->screen ? this->screen->getScreenName() : "N/A")
              << " | Time: " << this->startTime << "\n";
}

void Show::displaySeatLayout() const {
    std::cout << "\n========================================\n";
    std::cout << "SEAT LAYOUT FOR SHOW #" << this->showId << " (" 
              << (this->movie ? this->movie->getTitle() : "") << " - " 
              << (this->screen ? this->screen->getScreenName() : "") << " at " 
              << this->startTime << ")\n";
    std::cout << "========================================\n";

    std::string currentRow = "";
    for (size_t i = 0; i < this->showSeats.size(); ++i) {
        const auto& seat = this->showSeats[i];
        std::string num = seat.getSeatNumber();
        std::string row = (num.length() > 0) ? num.substr(0, 1) : "";

        if (row != currentRow) {
            if (!currentRow.empty()) {
                std::cout << "\n";
            }
            currentRow = row;
            std::cout << "Row " << currentRow << " (" << seat.getSeatTypeString() << "):\n  ";
        }

        std::cout << std::left << std::setw(4) << num 
                  << "[" << (seat.isAvailable() ? "AVAILABLE" : "BOOKED") << "]   ";

        if ((i + 1) % 5 == 0 && (i + 1) < this->showSeats.size()) {
            std::cout << "\n  ";
        }
    }
    std::cout << "\n========================================\n\n";
}
