#include "CashPayment.h"
#include <iostream>

CashPayment::CashPayment(double amountTendered)
    : Payment("Cash") {
    this->amountTendered = amountTendered;
}

// Runtime Polymorphism: Payment pointer invokes this derived implementation at runtime
bool CashPayment::pay(double amount) {
    std::cout << "\n[Cash Counter] Received cash: ₹" << this->amountTendered 
              << " for required amount: ₹" << amount << "...\n";

    if (this->amountTendered < amount) {
        std::cout << "[Cash Counter] Payment FAILED: Insufficient cash provided. Short by ₹" 
                  << (amount - this->amountTendered) << ".\n";
        return false;
    }

    double change = this->amountTendered - amount;
    std::cout << "[Cash Counter] ₹" << amount << " accepted. Change returned: ₹" << change << ".\n";
    return true;
}

double CashPayment::getAmountTendered() const {
    return this->amountTendered;
}
