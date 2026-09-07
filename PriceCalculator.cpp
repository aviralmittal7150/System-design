#include "PriceCalculator.h"

// Compile-Time Polymorphism (Overload 1)
double PriceCalculator::calculatePrice(SeatType type) const {
    switch (type) {
        case SeatType::SILVER:
            return SILVER_PRICE;
        case SeatType::GOLD:
            return GOLD_PRICE;
        case SeatType::PLATINUM:
            return PLATINUM_PRICE;
        default:
            return 0.0;
    }
}

// Compile-Time Polymorphism (Overload 2)
double PriceCalculator::calculatePrice(SeatType type, int quantity) const {
    if (quantity <= 0) {
        return 0.0;
    }
    return calculatePrice(type) * quantity;
}

// Compile-Time Polymorphism (Overload 3)
double PriceCalculator::calculatePrice(const std::vector<const ShowSeat*>& seats) const {
    double total = 0.0;
    for (const auto* seat : seats) {
        if (seat != nullptr) {
            total += calculatePrice(seat->getSeatType());
        }
    }
    return total;
}
