#include "Tenant.h"
#include <iostream>
#include <iomanip>

Tenant::Tenant() {
    tenantId = 0;
    name = "";
    phone = "";
}

Tenant::Tenant(int id, const std::string& tenantName, const std::string& phoneNumber) {
    tenantId = id;
    name = tenantName;
    phone = phoneNumber;
}

int Tenant::getId() const {
    return tenantId;
}

std::string Tenant::getName() const {
    return name;
}

std::string Tenant::getPhone() const {
    return phone;
}

void Tenant::updateDetails(const std::string& tenantName, const std::string& phoneNumber) {
    name = tenantName;
    phone = phoneNumber;
}

void Tenant::display() const {
    std::cout << std::left 
              << std::setw(12) << tenantId 
              << std::setw(25) << name 
              << phone << "\n";
}
