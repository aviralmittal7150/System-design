#ifndef CARD_PAYMENT_H
#define CARD_PAYMENT_H

#include "Payment.h"

// Derived Class: CardPayment
// Demonstrates Inheritance: CardPayment is-a Payment.
// Implements Runtime Polymorphism for Credit/Debit Card transactions.
class CardPayment : public Payment {
private:
    std::string cardNumber;
    std::string cardHolderName;
    std::string cvv;

public:
    CardPayment(const std::string& cardNumber, const std::string& cardHolderName, const std::string& cvv);

    bool pay(double amount) override;

    std::string getCardNumberMasked() const;
};

#endif // CARD_PAYMENT_H
