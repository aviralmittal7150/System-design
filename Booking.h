#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include "Customer.h"
#include "Show.h"
#include "ShowSeat.h"
#include "BookingStatus.h"

// Entity / Transaction Class: Booking
// Responsibility: Represents an individual ticket reservation transaction.
// Relationships:
// - Aggregation with Customer (Booking has-a Customer; Customer exists independently).
// - Aggregation with Show (Booking references a Show; Show exists independently).
// - Aggregation with ShowSeat (Booking references ShowSeat objects; ShowSeat lifecycle tied to Show).
class Booking {
private:
    // Static Member: Generates unique consecutive booking IDs across all instances
    static int nextBookingId;

    // Encapsulation: Private members protecting transaction details
    std::string bookingId;
    Customer customer;
    const Show* show;
    std::vector<ShowSeat*> bookedSeats;
    double totalAmount;
    std::string paymentMethod;
    BookingStatus status;

public:
    Booking(const Customer& customer, const Show* show, const std::vector<ShowSeat*>& bookedSeats, 
            double totalAmount, const std::string& paymentMethod);

    // Static method for resetting or inspecting next ID generator (useful for testing/viva)
    static void resetNextBookingId(int startId = 1001);

    std::string getBookingId() const;
    const Customer& getCustomer() const;
    const Show* getShow() const;
    const std::vector<ShowSeat*>& getBookedSeats() const;
    double getTotalAmount() const;
    std::string getPaymentMethod() const;
    BookingStatus getStatus() const;
    std::string getStatusString() const;

    // Encapsulation: Controlled cancellation method
    bool cancel();
};

#endif // BOOKING_H
