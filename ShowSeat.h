#ifndef SHOW_SEAT_H
#define SHOW_SEAT_H

#include "Seat.h"
#include "SeatStatus.h"

// Entity Class: ShowSeat
// Responsibility: Represents the dynamic availability status of ONE physical seat for ONE particular show.
// Demonstrates Aggregation/Association with physical Seat: Points to physical Seat metadata, but manages its own availability.
class ShowSeat {
private:
    const Seat* physicalSeat;
    // Encapsulation: seat status is private and modified through controlled methods only.
    SeatStatus status;

public:
    explicit ShowSeat(const Seat* physicalSeat);

    const Seat* getPhysicalSeat() const;
    std::string getSeatNumber() const;
    SeatType getSeatType() const;
    std::string getSeatTypeString() const;
    SeatStatus getStatus() const;
    std::string getStatusString() const;

    bool isAvailable() const;

    // Encapsulation: State-mutating controlled methods
    bool book();
    void release();
};

#endif // SHOW_SEAT_H
