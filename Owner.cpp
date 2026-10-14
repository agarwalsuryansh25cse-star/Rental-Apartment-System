#include "Owner.h"
#include <iostream>
#include <iomanip>

Owner::Owner() {
    ownerId = 0;
    name = "";
    phone = "";
}

Owner::Owner(int id, const std::string& ownerName, const std::string& phoneNumber) {
    ownerId = id;
    name = ownerName;
    phone = phoneNumber;
}

int Owner::getId() const {
    return ownerId;
}

std::string Owner::getName() const {
    return name;
}

std::string Owner::getPhone() const {
    return phone;
}

void Owner::updateDetails(const std::string& ownerName, const std::string& phoneNumber) {
    name = ownerName;
    phone = phoneNumber;
}

void Owner::display() const {
    std::cout << std::left 
              << std::setw(12) << ownerId 
              << std::setw(25) << name 
              << phone << "\n";
}
