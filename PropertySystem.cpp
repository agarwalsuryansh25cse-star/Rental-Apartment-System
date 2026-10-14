#include "PropertySystem.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <limits>

namespace {
    int readInt(const std::string& prompt, int minimum = 1) {
        int val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val && val >= minimum) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            std::cout << "Invalid input. Please enter a whole number >= " << minimum << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    double readMoney(const std::string& prompt) {
        double val;
        while (true) {
            std::cout << prompt;
            if (std::cin >> val && val > 0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return val;
            }
            std::cout << "Invalid amount. Enter a positive number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string readText(const std::string& prompt) {
        std::string val;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, val);
            if (!val.empty() && val.find('|') == std::string::npos) {
                return val;
            }
            std::cout << "Input cannot be empty or contain '|'. Please try again.\n";
        }
    }
}

PropertySystem::PropertySystem() {
    nextAgreementId = 1;
}

int PropertySystem::findOwnerIndex(int id) const {
    for (size_t i = 0; i < owners.size(); ++i) {
        if (owners[i].getId() == id) return static_cast<int>(i);
    }
    return -1;
}

int PropertySystem::findPropertyIndex(int id) const {
    for (size_t i = 0; i < properties.size(); ++i) {
        if (properties[i].getId() == id) return static_cast<int>(i);
    }
    return -1;
}

int PropertySystem::findTenantIndex(int id) const {
    for (size_t i = 0; i < tenants.size(); ++i) {
        if (tenants[i].getId() == id) return static_cast<int>(i);
    }
    return -1;
}

int PropertySystem::findAgreementIndex(int id) const {
    for (size_t i = 0; i < agreements.size(); ++i) {
        if (agreements[i].getId() == id) return static_cast<int>(i);
    }
    return -1;
}

void PropertySystem::addOwner() {
    int id = readInt("Enter Owner ID: ");
    if (findOwnerIndex(id) != -1) {
        std::cout << "An owner with this ID already exists.\n";
        return;
    }
    std::string name = readText("Enter Owner Name: ");
    std::string phone = readText("Enter Owner Phone: ");

    owners.push_back(Owner(id, name, phone));
    std::cout << "Owner added successfully.\n";
}

void PropertySystem::addProperty() {
    int id = readInt("Enter Property ID: ");
    if (findPropertyIndex(id) != -1) {
        std::cout << "A property with this ID already exists.\n";
        return;
    }
    std::string address = readText("Enter Property Address: ");
    std::string type = readText("Enter Property Type (Apartment/Flat/Villa): ");
    double rent = readMoney("Enter Monthly Rent: ");
    int ownerId = readInt("Enter Owner ID: ");

    if (findOwnerIndex(ownerId) == -1) {
        std::cout << "Error: Owner does not exist. Add owner first.\n";
        return;
    }

    properties.push_back(Property(id, address, type, rent, ownerId));
    std::cout << "Property added successfully.\n";
}

void PropertySystem::addTenant() {
    int id = readInt("Enter Tenant ID: ");
    if (findTenantIndex(id) != -1) {
        std::cout << "A tenant with this ID already exists.\n";
        return;
    }
    std::string name = readText("Enter Tenant Name: ");
    std::string phone = readText("Enter Tenant Phone: ");

    tenants.push_back(Tenant(id, name, phone));
    std::cout << "Tenant added successfully.\n";
}

void PropertySystem::addRecord() {
    std::cout << "\n--- Add Record ---\n";
    std::cout << "1. Owner\n2. Property\n3. Tenant\n";
    int choice = readInt("Select type: ");
    if (choice == 1) addOwner();
    else if (choice == 2) addProperty();
    else if (choice == 3) addTenant();
    else std::cout << "Invalid choice.\n";
}

void PropertySystem::displayOwners() const {
    std::cout << "\n--- OWNERS ---\n";
    std::cout << std::left << std::setw(12) << "Owner ID" << std::setw(25) << "Name" << "Phone\n";
    if (owners.empty()) std::cout << "(No owners registered)\n";
    for (const auto& owner : owners) {
        owner.display();
    }
}

void PropertySystem::displayProperties() const {
    std::cout << "\n--- PROPERTIES ---\n";
    std::cout << std::left << std::setw(12) << "Property ID" << std::setw(28) << "Address" 
              << std::setw(16) << "Type" << std::right << std::setw(12) << "Rent" << "  "
              << std::left << std::setw(12) << "Status" << "Owner ID\n";
    if (properties.empty()) std::cout << "(No properties registered)\n";
    for (const auto& prop : properties) {
        prop.display();
    }
}

void PropertySystem::displayTenants() const {
    std::cout << "\n--- TENANTS ---\n";
    std::cout << std::left << std::setw(12) << "Tenant ID" << std::setw(25) << "Name" << "Phone\n";
    if (tenants.empty()) std::cout << "(No tenants registered)\n";
    for (const auto& tenant : tenants) {
        tenant.display();
    }
}

void PropertySystem::displayAgreements() const {
    std::cout << "\n--- RENTAL AGREEMENTS ---\n";
    std::cout << std::left << std::setw(14) << "Agreement ID" << std::setw(14) << "Property ID" 
              << std::setw(12) << "Tenant ID" << std::right << std::setw(12) << "Monthly Rent" 
              << std::setw(12) << "Months" << "  " << std::left << std::setw(14) << "Status" 
              << std::right << std::setw(13) << "Total Rent\n";
    if (agreements.empty()) std::cout << "(No agreements registered)\n";
    for (const auto& agreement : agreements) {
        agreement.display();
    }
}

void PropertySystem::displayRecords() const {
    displayOwners();
    displayProperties();
    displayTenants();
    displayAgreements();
}

void PropertySystem::searchRecord() const {
    std::cout << "\n--- Search Record ---\n";
    std::cout << "1. Owner\n2. Property\n3. Tenant\n4. Agreement\n";
    int choice = readInt("Enter choice: ");
    int id = readInt("Enter ID to search: ");

    if (choice == 1) {
        int idx = findOwnerIndex(id);
        if (idx == -1) std::cout << "Owner not found.\n";
        else owners[idx].display();
    } else if (choice == 2) {
        int idx = findPropertyIndex(id);
        if (idx == -1) std::cout << "Property not found.\n";
        else properties[idx].display();
    } else if (choice == 3) {
        int idx = findTenantIndex(id);
        if (idx == -1) std::cout << "Tenant not found.\n";
        else tenants[idx].display();
    } else if (choice == 4) {
        int idx = findAgreementIndex(id);
        if (idx == -1) std::cout << "Agreement not found.\n";
        else agreements[idx].display();
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void PropertySystem::updateRecord() {
    std::cout << "\n--- Update Record ---\n";
    std::cout << "1. Owner Details\n2. Property Details\n3. Tenant Details\n";
    int choice = readInt("Enter choice: ");
    int id = readInt("Enter ID: ");

    if (choice == 1) {
        int idx = findOwnerIndex(id);
        if (idx == -1) { std::cout << "Owner not found.\n"; return; }
        std::string name = readText("Enter new name: ");
        std::string phone = readText("Enter new phone: ");
        owners[idx].updateDetails(name, phone);
        std::cout << "Owner updated.\n";
    } else if (choice == 2) {
        int idx = findPropertyIndex(id);
        if (idx == -1) { std::cout << "Property not found.\n"; return; }
        std::string address = readText("Enter new address: ");
        std::string type = readText("Enter new type: ");
        double rent = readMoney("Enter new monthly rent: ");
        properties[idx].updateDetails(address, type, rent);
        std::cout << "Property updated.\n";
    } else if (choice == 3) {
        int idx = findTenantIndex(id);
        if (idx == -1) { std::cout << "Tenant not found.\n"; return; }
        std::string name = readText("Enter new name: ");
        std::string phone = readText("Enter new phone: ");
        tenants[idx].updateDetails(name, phone);
        std::cout << "Tenant updated.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void PropertySystem::deleteRecord() {
    std::cout << "\n--- Delete Record ---\n";
    std::cout << "1. Owner\n2. Property\n3. Tenant\n";
    int choice = readInt("Enter choice: ");
    int id = readInt("Enter ID: ");

    if (choice == 1) {
        int idx = findOwnerIndex(id);
        if (idx == -1) { std::cout << "Owner not found.\n"; return; }
        for (const auto& p : properties) {
            if (p.getOwnerId() == id) {
                std::cout << "Cannot delete: Owner has registered properties.\n";
                return;
            }
        }
        owners.erase(owners.begin() + idx);
        std::cout << "Owner deleted.\n";
    } else if (choice == 2) {
        int idx = findPropertyIndex(id);
        if (idx == -1) { std::cout << "Property not found.\n"; return; }
        for (const auto& a : agreements) {
            if (a.getPropertyId() == id) {
                std::cout << "Cannot delete: Property has agreement records.\n";
                return;
            }
        }
        properties.erase(properties.begin() + idx);
        std::cout << "Property deleted.\n";
    } else if (choice == 3) {
        int idx = findTenantIndex(id);
        if (idx == -1) { std::cout << "Tenant not found.\n"; return; }
        for (const auto& a : agreements) {
            if (a.getTenantId() == id) {
                std::cout << "Cannot delete: Tenant is associated with an agreement.\n";
                return;
            }
        }
        tenants.erase(tenants.begin() + idx);
        std::cout << "Tenant deleted.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void PropertySystem::processTransaction() {
    std::cout << "\n--- Transaction Process ---\n";
    std::cout << "1. Rent a Property\n2. Terminate Agreement\n";
    int choice = readInt("Select transaction: ");

    if (choice == 1) {
        int propId = readInt("Enter Property ID: ");
        int tenantId = readInt("Enter Tenant ID: ");
        int months = readInt("Enter Duration (months 1-120): ");

        if (months > 120) {
            std::cout << "Duration cannot exceed 120 months.\n";
            return;
        }

        int pIdx = findPropertyIndex(propId);
        int tIdx = findTenantIndex(tenantId);

        if (pIdx == -1) { std::cout << "Property not found.\n"; return; }
        if (tIdx == -1) { std::cout << "Tenant not found.\n"; return; }
        if (!properties[pIdx].isAvailable()) {
            std::cout << "Property is already rented.\n";
            return;
        }

        RentalAgreement agreement(nextAgreementId, propId, tenantId, properties[pIdx].getRent(), months);
        agreements.push_back(agreement);
        properties[pIdx].setStatus("Rented");
        std::cout << "Rental agreement created with ID: " << nextAgreementId << "\n";
        nextAgreementId++;
    } else if (choice == 2) {
        int aId = readInt("Enter Agreement ID: ");
        int aIdx = findAgreementIndex(aId);

        if (aIdx == -1) { std::cout << "Agreement not found.\n"; return; }
        if (agreements[aIdx].getStatus() == "Terminated") {
            std::cout << "Agreement is already terminated.\n";
            return;
        }

        int pIdx = findPropertyIndex(agreements[aIdx].getPropertyId());
        agreements[aIdx].terminate();
        if (pIdx != -1) {
            properties[pIdx].setStatus("Available");
        }
        std::cout << "Agreement terminated successfully.\n";
    } else {
        std::cout << "Invalid transaction.\n";
    }
}

void PropertySystem::report() const {
    int availableProps = 0;
    int rentedProps = 0;
    int activeAgreements = 0;
    int terminatedAgreements = 0;
    double totalRentActive = 0.0;

    for (const auto& p : properties) {
        if (p.getStatus() == "Available") availableProps++;
        else if (p.getStatus() == "Rented") rentedProps++;
    }

    for (const auto& a : agreements) {
        if (a.getStatus() == "Active") {
            activeAgreements++;
            totalRentActive += a.calculateRent();
        } else {
            terminatedAgreements++;
        }
    }

    std::cout << "\n=== SYSTEM SUMMARY REPORT ===\n";
    std::cout << "Total Owners: " << owners.size() << "\n";
    std::cout << "Total Properties: " << properties.size() << " (Available: " << availableProps << ", Rented: " << rentedProps << ")\n";
    std::cout << "Total Tenants: " << tenants.size() << "\n";
    std::cout << "Agreements: " << agreements.size() << " (Active: " << activeAgreements << ", Terminated: " << terminatedAgreements << ")\n";
    std::cout << "Total Expected Revenue: Rs. " << std::fixed << std::setprecision(2) << totalRentActive << "\n";
}

void PropertySystem::saveNow() const {
    FileManager::save(*this);
    std::cout << "All records saved to Data files.\n";
}

void PropertySystem::loadData() {
    FileManager::load(*this);
    std::cout << "Data loaded successfully.\n";
}

void PropertySystem::saveLoadMenu() {
    std::cout << "\n--- Save / Load Menu ---\n";
    std::cout << "1. Save Records Now\n2. Reload Records from Files\n";
    int choice = readInt("Select option: ");
    if (choice == 1) saveNow();
    else if (choice == 2) loadData();
    else std::cout << "Invalid option.\n";
}
