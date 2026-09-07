#include "Payment.h"

Payment::Payment(const std::string& methodName) {
    this->paymentMethodName = methodName;
}

std::string Payment::getPaymentMethodName() const {
    return this->paymentMethodName;
}
