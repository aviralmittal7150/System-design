#ifndef CASH_PAYMENT_H
#define CASH_PAYMENT_H

#include "Payment.h"

// Derived Class: CashPayment
// Demonstrates Inheritance: CashPayment is-a Payment.
// Implements Runtime Polymorphism for Box Office Cash transactions.
class CashPayment : public Payment {
private:
    double amountTendered;

public:
    explicit CashPayment(double amountTendered);

    bool pay(double amount) override;

    double getAmountTendered() const;
};

#endif // CASH_PAYMENT_H
