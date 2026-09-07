#include "CardPayment.h"
#include <iostream>

CardPayment::CardPayment(const std::string& cardNumber, const std::string& cardHolderName, const std::string& cvv)
    : Payment("Card") {
    this->cardNumber = cardNumber;
    this->cardHolderName = cardHolderName;
    this->cvv = cvv;
}

// Runtime Polymorphism: Payment pointer invokes this derived implementation at runtime
bool CardPayment::pay(double amount) {
    std::cout << "\n[Card Gateway] Authorizing card ending with " << getCardNumberMasked() << "...\n";
    
    // Simulate validation: 16-digit card number (or >= 12 digits) and 3-digit CVV
    if (this->cardNumber.length() < 12 || this->cvv.length() != 3 || this->cardNumber == "0000000000000000") {
        std::cout << "[Card Gateway] Payment FAILED: Card authorization failed or invalid details.\n";
        return false;
    }

    std::cout << "[Card Gateway] ₹" << amount << " successfully charged to Card (" << getCardNumberMasked() << ").\n";
    return true;
}

std::string CardPayment::getCardNumberMasked() const {
    if (this->cardNumber.length() >= 4) {
        return "XXXX-XXXX-XXXX-" + this->cardNumber.substr(this->cardNumber.length() - 4);
    }
    return "XXXX";
}
