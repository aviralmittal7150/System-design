#include "Customer.h"

Customer::Customer(const std::string& name, const std::string& phone) {
    // Using 'this' pointer to assign parameters to member variables
    this->name = name;
    this->phone = phone;
}

std::string Customer::getName() const {
    return this->name;
}

std::string Customer::getPhone() const {
    return this->phone;
}
