#include "UpiPayment.h"
#include <iostream>

UpiPayment::UpiPayment(const std::string& upiId) 
    : Payment("UPI") {
    this->upiId = upiId;
}

// Runtime Polymorphism: Payment pointer invokes this derived implementation at runtime
bool UpiPayment::pay(double amount) {
    std::cout << "\n[UPI Gateway] Connecting to UPI handle: " << this->upiId << "...\n";
    
    // Simulate validation: UPI ID must be non-empty and contain '@' and not be "fail"
    if (this->upiId.empty() || this->upiId.find('@') == std::string::npos || this->upiId == "fail@upi") {
        std::cout << "[UPI Gateway] Payment FAILED: Invalid or rejected UPI ID (" << this->upiId << ").\n";
        return false;
    }

    std::cout << "[UPI Gateway] ₹" << amount << " successfully debited via UPI (" << this->upiId << ").\n";
    return true;
}

std::string UpiPayment::getUpiId() const {
    return this->upiId;
}
