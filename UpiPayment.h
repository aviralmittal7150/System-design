#ifndef UPI_PAYMENT_H
#define UPI_PAYMENT_H

#include "Payment.h"

// Derived Class: UpiPayment
// Demonstrates Inheritance: UpiPayment is-a Payment.
// Implements Runtime Polymorphism for UPI transactions.
class UpiPayment : public Payment {
private:
    std::string upiId;

public:
    explicit UpiPayment(const std::string& upiId);

    // Overridden virtual method for processing UPI payment
    bool pay(double amount) override;

    std::string getUpiId() const;
};

#endif // UPI_PAYMENT_H
