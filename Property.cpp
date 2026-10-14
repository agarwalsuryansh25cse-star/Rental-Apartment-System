#include "Property.h"
#include <iostream>
#include <iomanip>

Property::Property() {
    propertyId = 0;
    address = "";
    type = "";
    status = "Available";
    rent = 0.0;
    ownerId = 0;
}

Property::Property(int id, const std::string& propertyAddress, const std::string& propertyType, 
                   double monthlyRent, int propertyOwnerId, const std::string& propertyStatus) {
    propertyId = id;
    address = propertyAddress;
    type = propertyType;
    rent = monthlyRent;
    ownerId = propertyOwnerId;
    status = propertyStatus;
}

int Property::getId() const {
    return propertyId;
}

std::string Property::getAddress() const {
    return address;
}

std::string Property::getType() const {
    return type;
}

double Property::getRent() const {
    return rent;
}

std::string Property::getStatus() const {
    return status;
}

int Property::getOwnerId() const {
    return ownerId;
}

bool Property::isAvailable() const {
    return status == "Available";
}

void Property::updateDetails(const std::string& newAddress, const std::string& newType, double newRent) {
    address = newAddress;
    type = newType;
    rent = newRent;
}

void Property::setStatus(const std::string& newStatus) {
    status = newStatus;
}

void Property::display() const {
    std::cout << std::left 
              << std::setw(12) << propertyId 
              << std::setw(28) << address 
              << std::setw(16) << type 
              << std::right << std::setw(12) << std::fixed << std::setprecision(2) << rent << "  "
              << std::left << std::setw(12) << status 
              << ownerId << "\n";
}
