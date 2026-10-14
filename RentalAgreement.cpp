#include "RentalAgreement.h"
#include <iostream>
#include <iomanip>

RentalAgreement::RentalAgreement() {
    agreementId = 0;
    propertyId = 0;
    tenantId = 0;
    durationMonths = 0;
    monthlyRent = 0.0;
    status = "Active";
}

RentalAgreement::RentalAgreement(int aId, int pId, int tId, double rent, int months, const std::string& s) {
    agreementId = aId;
    propertyId = pId;
    tenantId = tId;
    monthlyRent = rent;
    durationMonths = months;
    status = s;
}

int RentalAgreement::getId() const {
    return agreementId;
}

int RentalAgreement::getPropertyId() const {
    return propertyId;
}

int RentalAgreement::getTenantId() const {
    return tenantId;
}

double RentalAgreement::getMonthlyRent() const {
    return monthlyRent;
}

int RentalAgreement::getDurationMonths() const {
    return durationMonths;
}

std::string RentalAgreement::getStatus() const {
    return status;
}

double RentalAgreement::calculateRent() const {
    return monthlyRent * durationMonths;
}

void RentalAgreement::terminate() {
    status = "Terminated";
}

void RentalAgreement::display() const {
    std::cout << std::left 
              << std::setw(14) << agreementId 
              << std::setw(14) << propertyId 
              << std::setw(12) << tenantId 
              << std::right << std::setw(12) << std::fixed << std::setprecision(2) << monthlyRent 
              << std::setw(12) << durationMonths << "  "
              << std::left << std::setw(14) << status 
              << std::right << std::setw(13) << calculateRent() << "\n";
}
