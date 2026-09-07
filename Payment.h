#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

// Abstract Class: Payment
// Demonstrates Abstraction & Interface Contract: Defines an abstract base interface for processing payments.
// Demonstrates Liskov Substitution Principle (LSP): Derived payment types can be substituted anywhere Payment* is used.
// Demonstrates Interface Segregation Principle (ISP): Keeps payment contract focused on paying without forcing unnecessary refund/reversal methods.
class Payment {
protected:
    std::string paymentMethodName;

public:
    explicit Payment(const std::string& methodName);
    virtual ~Payment() = default;

    // Pure virtual method demonstrating Abstraction and Runtime Polymorphism
    virtual bool pay(double amount) = 0;

    std::string getPaymentMethodName() const;
};

#endif // PAYMENT_H
