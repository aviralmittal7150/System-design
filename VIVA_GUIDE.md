# VIVA PREPARATION & SYSTEM DESIGN DEFENSE GUIDE
**Course**: B.Tech CSE Semester 5 — Object-Oriented Analysis & System Design  
**Project**: Movie Ticket Booking System for a Single Cinema  
**Author**: Aviral Mittal

---

## 1. ELEVATOR PITCH / 2-MINUTE ARCHITECTURE SUMMARY

> *"Our project is a modular, menu-driven Movie Ticket Booking System in modern C++ (C++17) designed for a single cinema theatre. The architecture strictly follows Object-Oriented Design and SOLID principles.*
>
> *The system is divided into three distinct layers:*
> 1. * **Domain Entities Layer**: `Movie`, `Seat`, `Screen`, `Cinema`, `Show`, `ShowSeat`, and `Customer` model the real-world cinema structure with clear lifetime semantics (e.g., `Screen` composed of `Seat`s; `Show` aggregating `Movie` and `Screen` while owning dynamic `ShowSeat`s).*
> 2. * **Payment & Pricing Layer**: An abstract `Payment` interface with pure virtual `pay(double)` enables runtime polymorphism across `UpiPayment`, `CardPayment`, and `CashPayment`. `PriceCalculator` encapsulates seat tier pricing with function overloading and zero magic numbers.*
> 3. * **Service & Orchestration Layer**: `BookingService` manages transactions, atomic seat locking, and payment validation with rollback guarantees. `TicketPrinter` formats output independently.
>
> *The design adheres to SRP, OCP, LSP, ISP, and DIP, and passes all edge cases including payment failure rollbacks, duplicate booking rejection, and cancellation seat release."*

---

## 2. TOP VIVA QUESTIONS & TARGET ANSWERS

### Q1: Why is `ShowSeat` separated from `Seat`?
**Answer**:  
`Seat` represents a **physical seat** in an auditorium with fixed attributes (seat number `A1`, tier `SILVER`). Its state does not change across different movie timings.  
`ShowSeat` represents the **transient state of that physical seat for a specific screening time**. A seat might be booked for the 7:30 PM show but available for the 10:30 PM show. Separating them prevents mutable state corruption across multiple shows and avoids data duplication.

---

### Q2: How did you prove Composition vs Aggregation using the Lifetime Test?
**Answer**:  
We apply the Lifetime Test: *"If the container object is destroyed, does the contained object also die?"*
- **Composition (`Cinema ◆── Screen` and `Screen ◆── Seat`)**: If the cinema building or screen auditorium is demolished/destroyed, the physical seats within it cease to exist.
- **Composition (`Show ◆── ShowSeat`)**: A `ShowSeat` exists purely for the duration of that specific show screening. If the show is deleted, its `ShowSeat` status mappings die.
- **Aggregation (`Show ◇── Movie` and `Show ◇── Screen`)**: If a show is cancelled or finished, the `Movie` still exists in the movie catalog, and the `Screen` auditorium remains intact for future shows.
- **Aggregation (`Booking ◇── Customer`)**: If a booking is deleted or cancelled, the `Customer` record remains independent.

---

### Q3: Where is Runtime Polymorphism used, and what enables it in C++?
**Answer**:  
Runtime polymorphism is implemented in the Payment hierarchy:
- Base class `Payment` defines `virtual bool pay(double amount) = 0;` (pure virtual function) and a virtual destructor.
- Derived classes `UpiPayment`, `CardPayment`, and `CashPayment` override `pay()`.
- In `BookingService::createBooking`, a `Payment*` base pointer is passed. When `payment->pay(totalAmount)` is invoked, dynamic dispatch occurs through the **vtable (virtual table)**, routing execution to the concrete derived class method at runtime.

---

### Q4: How does your code satisfy the Dependency Inversion Principle (DIP)?
**Answer**:  
High-level modules should not depend on low-level modules; both should depend on abstractions.  
`BookingService` (high-level orchestration) does not instantiate concrete payment classes like `new CardPayment()` or `new UpiPayment()`. Instead, `BookingService` depends solely on the abstract `Payment*` interface contract. Concrete payment instances are injected at runtime from the UI layer (`CinemaApp`).

---

### Q5: How is Compile-Time Polymorphism demonstrated in your code?
**Answer**:  
Through **function/method overloading** in service classes:
1. `PriceCalculator::calculatePrice(SeatType type)` (single seat tier calculation).
2. `PriceCalculator::calculatePrice(SeatType type, int quantity)` (multiple seats of same tier).
3. `PriceCalculator::calculatePrice(const vector<const ShowSeat*>& seats)` (heterogeneous list of show seats).
4. `TicketPrinter::printTicket(const Booking&)` vs `TicketPrinter::printTicket(const Booking&, std::ostream&)` for stream flexibility.

---

### Q6: How does the system handle transactional rollbacks on payment failure?
**Answer**:  
The booking process is atomic:
1. First, all requested seats are validated for existence and `AVAILABLE` status.
2. The total price is calculated.
3. The payment is processed via `payment->pay(totalAmount)`.
4. Only if `payment->pay()` returns `true` are the seats marked `BOOKED` and the `Booking` entity created.
5. If payment returns `false` (e.g. invalid UPI, declined card, or insufficient cash), the function aborts immediately, leaving the `ShowSeat` objects in their original `AVAILABLE` state and creating no booking record.

---

### Q7: What feature did you deliberately NOT implement and why?
**Answer**:  
We deliberately did not implement external SQL/NoSQL database persistence.  
**Justification**: The assignment specifies a self-contained, single-cinema console application. Adding external database drivers would introduce third-party system dependencies without enhancing the evaluation of core OOP and System Design principles. In-memory data structures managed via RAII and smart pointers provide clean, deterministic lifecycle management.

---

### Q8: What is the purpose of `static int nextBookingId` in `Booking`?
**Answer**:  
`static int nextBookingId` is a class-level variable shared across all instances of `Booking`. It ensures that every new booking receives an auto-incrementing, globally unique identifier (e.g. `B1001`, `B1002`, `B1003`) without requiring an external database sequence generator.

---

### Q9: Why did you use `std::unique_ptr` and `const` references?
**Answer**:  
1. `std::unique_ptr` enforces **Resource Acquisition Is Initialization (RAII)** and explicit ownership semantics (e.g. `BookingService` uniquely owns created `Booking` records). It eliminates memory leaks and dangling pointers.
2. `const` references (`const Movie*`, `const std::string&`) enforce read-only immutability, prevent accidental state mutations, and avoid expensive object copying.

---

## 3. QUICK CODE NAVIGATION CHEAT SHEET

| Question Area | Primary File | Primary Lines / Symbols |
| :--- | :--- | :--- |
| **Encapsulation & Mutators** | `ShowSeat.h` / `ShowSeat.cpp` | `ShowSeat::book()`, `ShowSeat::release()` |
| **Abstract Base Class** | `Payment.h` | `virtual bool pay(double amount) = 0;` |
| **Derived Implementations** | `UpiPayment.cpp`, `CardPayment.cpp`, `CashPayment.cpp` | `override pay(double amount)` |
| **Runtime Polymorphism** | `BookingService.cpp` | `payment->pay(totalAmount)` |
| **Function Overloading** | `PriceCalculator.h` | `calculatePrice(...)` overloads |
| **Composition** | `Screen.h` / `Cinema.h` | `std::vector<Seat> seats`, `std::vector<Screen> screens` |
| **Static Member** | `Booking.h` / `Booking.cpp` | `static int nextBookingId = 1001;` |
| **Atomic Booking & Rollback** | `BookingService.cpp` | `BookingService::createBooking(...)` |
| **Cancellation Logic** | `Booking.cpp` / `BookingService.cpp` | `Booking::cancel()`, `BookingService::cancelBooking(...)` |
