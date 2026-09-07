#include <iostream>
#include <cassert>
#include "Cinema.h"
#include "Movie.h"
#include "Screen.h"
#include "Show.h"
#include "Customer.h"
#include "BookingService.h"
#include "UpiPayment.h"
#include "CardPayment.h"
#include "CashPayment.h"
#include "PriceCalculator.h"

void runAllTests() {
    std::cout << "\n=======================================================\n";
    std::cout << "  RUNNING AUTOMATED VERIFICATION & TEST SUITE\n";
    std::cout << "=======================================================\n\n";

    // Setup Domain Data
    Movie movie1("Interstellar", "English", 169);
    Movie movie2("Avengers: Endgame", "English", 181);

    Screen screen1(1);
    screen1.addSeat(Seat("A1", SeatType::SILVER));
    screen1.addSeat(Seat("A2", SeatType::SILVER));
    screen1.addSeat(Seat("B1", SeatType::GOLD));
    screen1.addSeat(Seat("B2", SeatType::GOLD));
    screen1.addSeat(Seat("C1", SeatType::PLATINUM));

    Cinema cinema("PVR Cinemas");
    cinema.addScreen(screen1);

    const Screen* sc1 = cinema.findScreen(1);
    Show show1(1, &movie1, sc1, "07:30 PM");

    Customer customer1("Aviral Mittal", "9876543210");
    Customer customer2("John Doe", "9123456780");

    BookingService service;
    Booking::resetNextBookingId(1001);

    // Test 1: Price Calculator Overloading and Correct Values
    std::cout << "[Test 1] PriceCalculator verification...";
    PriceCalculator calc;
    assert(calc.calculatePrice(SeatType::SILVER) == 150.0);
    assert(calc.calculatePrice(SeatType::GOLD) == 250.0);
    assert(calc.calculatePrice(SeatType::PLATINUM) == 400.0);
    assert(calc.calculatePrice(SeatType::GOLD, 3) == 750.0);
    std::cout << " PASSED!\n";

    // Test 2: Successful Booking of one SILVER seat with UPI
    std::cout << "[Test 2] Successful booking with UPI (Seat A1)...";
    UpiPayment upiSuccess("aviral@okaxis");
    Booking* b1 = service.createBooking(customer1, &show1, {"A1"}, &upiSuccess);
    assert(b1 != nullptr);
    assert(b1->getBookingId() == "B1001");
    assert(b1->getTotalAmount() == 150.0);
    assert(b1->getStatus() == BookingStatus::CONFIRMED);
    assert(!show1.findShowSeat("A1")->isAvailable());
    std::cout << " PASSED!\n";

    // Test 3: Reject Already-Booked Seat
    std::cout << "[Test 3] Reject already-booked seat (Seat A1)...";
    UpiPayment upiSuccess2("john@okicici");
    Booking* bDuplicate = service.createBooking(customer2, &show1, {"A1"}, &upiSuccess2);
    assert(bDuplicate == nullptr);
    std::cout << " PASSED!\n";

    // Test 4: Reject Invalid Seat Number (e.g. Z99)
    std::cout << "[Test 4] Reject invalid seat number (Seat Z99)...";
    Booking* bInvalid = service.createBooking(customer2, &show1, {"Z99"}, &upiSuccess2);
    assert(bInvalid == nullptr);
    std::cout << " PASSED!\n";

    // Test 5: Payment Failure Rollback (Seat remains AVAILABLE)
    std::cout << "[Test 5] Payment failure rollback (Seat B1 with fail@upi)...";
    UpiPayment upiFail("fail@upi");
    assert(show1.findShowSeat("B1")->isAvailable());
    Booking* bFail = service.createBooking(customer2, &show1, {"B1"}, &upiFail);
    assert(bFail == nullptr);
    // Crucial check: Seat B1 MUST still be AVAILABLE
    assert(show1.findShowSeat("B1")->isAvailable());
    std::cout << " PASSED!\n";

    // Test 6: Multi-seat booking across multiple tiers (B1 GOLD + C1 PLATINUM = 250 + 400 = 650)
    std::cout << "[Test 6] Multi-seat booking across tiers (B1 GOLD + C1 PLATINUM)...";
    CardPayment card("1234567890123456", "John Doe", "123");
    Booking* b2 = service.createBooking(customer2, &show1, {"B1", "C1"}, &card);
    assert(b2 != nullptr);
    assert(b2->getBookingId() == "B1002");
    assert(b2->getTotalAmount() == 650.0);
    assert(!show1.findShowSeat("B1")->isAvailable());
    assert(!show1.findShowSeat("C1")->isAvailable());
    std::cout << " PASSED!\n";

    // Test 7: Cancellation of booking releases seats
    std::cout << "[Test 7] Booking cancellation releases seats...";
    bool cancelSuccess = service.cancelBooking("B1002");
    assert(cancelSuccess);
    assert(b2->getStatus() == BookingStatus::CANCELLED);
    // Both B1 and C1 must now be AVAILABLE again
    assert(show1.findShowSeat("B1")->isAvailable());
    assert(show1.findShowSeat("C1")->isAvailable());
    std::cout << " PASSED!\n";

    // Test 8: Re-booking seats that were previously cancelled
    std::cout << "[Test 8] Re-booking released seats (B1 & C1 with Cash)...";
    CashPayment cash(700.0); // ₹700 tendered for ₹650 bill
    Booking* b3 = service.createBooking(customer1, &show1, {"B1", "C1"}, &cash);
    assert(b3 != nullptr);
    assert(b3->getBookingId() == "B1003");
    assert(b3->getTotalAmount() == 650.0);
    assert(!show1.findShowSeat("B1")->isAvailable());
    assert(!show1.findShowSeat("C1")->isAvailable());
    std::cout << " PASSED!\n";

    std::cout << "\n=======================================================\n";
    std::cout << "  ALL 8 SYSTEM DESIGN TEST SUITES PASSED (100% SUCCESS)!\n";
    std::cout << "=======================================================\n\n";
}

int main() {
    runAllTests();
    return 0;
}
