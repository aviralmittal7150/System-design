#ifndef TICKET_PRINTER_H
#define TICKET_PRINTER_H

#include <iostream>
#include "Booking.h"

// Service Class: TicketPrinter
// Single Responsibility Principle (SRP): Responsible solely for formatting and rendering ticket output.
// Must NOT book seats, calculate prices, or process payments.
// Demonstrates Compile-Time Polymorphism via function overloading.
class TicketPrinter {
public:
    TicketPrinter() = default;

    // Compile-Time Polymorphism (Overload 1): Print formatted ticket to standard output (std::cout)
    void printTicket(const Booking& booking) const;

    // Compile-Time Polymorphism (Overload 2): Print formatted ticket to a specified output stream
    void printTicket(const Booking& booking, std::ostream& out) const;

    // Compile-Time Polymorphism (Overload 3): Print a one-line concise summary
    void printSummary(const Booking& booking) const;
};

#endif // TICKET_PRINTER_H
