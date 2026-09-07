#ifndef PRICE_CALCULATOR_H
#define PRICE_CALCULATOR_H

#include <vector>
#include "SeatType.h"
#include "ShowSeat.h"

// Service Class: PriceCalculator
// Single Responsibility Principle (SRP): Responsible solely for calculating seat costs and totals.
// Compile-time Polymorphism: Demonstrates function overloading for pricing different seat representations.
class PriceCalculator {
public:
    // Defined constants for seat pricing - eliminates magic numbers
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    PriceCalculator() = default;

    // Compile-Time Polymorphism (Overload 1): Calculate price for a single seat type
    double calculatePrice(SeatType type) const;

    // Compile-Time Polymorphism (Overload 2): Calculate price for a seat type with quantity
    double calculatePrice(SeatType type, int quantity) const;

    // Compile-Time Polymorphism (Overload 3): Calculate total price for a collection of selected show seats
    double calculatePrice(const std::vector<const ShowSeat*>& seats) const;
};

#endif // PRICE_CALCULATOR_H
