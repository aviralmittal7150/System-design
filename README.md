# Movie Ticket Booking System — Single Cinema
**System Design Assignment 1 | B.Tech CSE Semester 5**  
**Author**: Aviral Mittal ([aviralmittal7150](https://github.com/aviralmittal7150))  
**Repository**: [https://github.com/aviralmittal7150/System-design](https://github.com/aviralmittal7150/System-design)

---

## 📌 Project Overview
A modular, object-oriented C++17 console application simulating a Movie Ticket Booking System for a single cinema. Built adhering to strict System Design principles, clean code standards, OOP concepts (Encapsulation, Abstraction, Inheritance, Polymorphism, Composition, Aggregation, Association), and SOLID architecture.

---

## 🛠️ Key Features
1. **Movie Listing**: List all movies currently playing with language and duration.
2. **Show Scheduling**: View shows filtered by movie, screen number, and start time.
3. **Dynamic Seat Layout**: Visual rendering of screen seat tiers (`SILVER`, `GOLD`, `PLATINUM`) with real-time `[AVAILABLE]` or `[BOOKED]` status.
4. **Validation & Atomic Booking**: Supports multi-seat reservations, rejecting duplicate or invalid seats.
5. **Dynamic Price Calculation**: Tiered pricing without magic numbers (`SILVER` = ₹150, `GOLD` = ₹250, `PLATINUM` = ₹400).
6. **Polymorphic Payment Gateways**: Abstract `Payment` interface with `UPI`, `Card`, and `Cash` implementations. Rollback on failure keeps seats `AVAILABLE`.
7. **Ticket Formatting**: Formats and prints tickets containing Booking ID, movie, screen, showtime, seat breakdown, amount, payment method, and status.
8. **Booking Cancellation**: Cancels confirmed reservations and restores seats back to `AVAILABLE`.

---

## 📂 Project Structure
```
├── SeatType.h              # Enum for SILVER, GOLD, PLATINUM
├── SeatStatus.h            # Enum for AVAILABLE, BOOKED
├── BookingStatus.h         # Enum for CONFIRMED, CANCELLED, FAILED
├── Movie.h / Movie.cpp     # Movie domain entity
├── Seat.h / Seat.cpp       # Physical seat entity
├── Screen.h / Screen.cpp   # Auditorium screen (owns Seats)
├── Cinema.h / Cinema.cpp   # Cinema entity (owns Screens)
├── ShowSeat.h / ShowSeat.cpp # Transient seat status for a show
├── Show.h / Show.cpp       # Movie screening (owns ShowSeats, aggregates Movie/Screen)
├── Customer.h / Customer.cpp # Customer entity
├── Payment.h / Payment.cpp # Abstract base payment class (virtual bool pay())
├── UpiPayment.h / UpiPayment.cpp   # UPI payment implementation
├── CardPayment.h / CardPayment.cpp # Card payment implementation
├── CashPayment.h / CashPayment.cpp # Cash payment implementation
├── PriceCalculator.h / PriceCalculator.cpp # SRP Price calculation service
├── TicketPrinter.h / TicketPrinter.cpp     # SRP Ticket rendering service
├── Booking.h / Booking.cpp # Booking transaction entity with static nextBookingId
├── BookingService.h / BookingService.cpp   # Workflow orchestration service
├── CinemaApp.h / CinemaApp.cpp             # Interactive console UI orchestrator
├── main.cpp                # Application entry point
├── test_suite.cpp          # Automated verification test harness
├── Makefile                # Build and test automation
├── ASSIGNMENT_REPORT.md    # Complete assignment documentation & UML diagrams
└── VIVA_GUIDE.md           # Semester 5 Viva Q&A defense preparation guide
```

---

## 🚀 Quick Start

### Build & Run
```bash
# Build the project
make

# Run the interactive console application
./movie_booking_system
```

### Run Automated Test Suite
```bash
# Run 8 comprehensive test scenarios verifying all requirements & edge cases
make test
```

---

## 📊 Documentation Links
- Detailed requirements, noun-verb analysis, relationship table, UML class & sequence diagrams, and SOLID mapping: **[ASSIGNMENT_REPORT.md](ASSIGNMENT_REPORT.md)**
- Comprehensive Semester 5 Viva Q&A preparation guide: **[VIVA_GUIDE.md](VIVA_GUIDE.md)**
