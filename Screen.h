#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include "Seat.h"

// Entity Class: Screen
// Responsibility: Represents an auditorium/screen in the cinema.
// Demonstrates Composition: Screen owns its collection of physical Seat objects.
// Lifetime Test: If Screen is destroyed, its physical Seat objects cease to exist.
class Screen {
private:
    int screenNumber;
    // Composition: Screen owns its Seat objects directly by value
    std::vector<Seat> seats;

public:
    explicit Screen(int screenNumber);

    int getScreenNumber() const;
    std::string getScreenName() const;

    void addSeat(const Seat& seat);
    const std::vector<Seat>& getSeats() const;
    const Seat* findSeat(const std::string& seatNumber) const;
};

#endif // SCREEN_H
