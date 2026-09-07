#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// Entity Class: Customer
// Responsibility: Stores customer contact information.
// Must NOT directly manipulate payment internals or manage seat state.
class Customer {
private:
    // Encapsulation: Customer attributes are kept private
    std::string name;
    std::string phone;

public:
    Customer(const std::string& name, const std::string& phone);

    std::string getName() const;
    std::string getPhone() const;
};

#endif // CUSTOMER_H
