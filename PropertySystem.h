#ifndef PROPERTYSYSTEM_H
#define PROPERTYSYSTEM_H

#include <vector>
#include "Owner.h"
#include "Property.h"
#include "Tenant.h"
#include "RentalAgreement.h"

class FileManager;

class PropertySystem {
private:
    std::vector<Owner> owners;
    std::vector<Property> properties;
    std::vector<Tenant> tenants;
    std::vector<RentalAgreement> agreements;
    int nextAgreementId;

    // Helper search functions
    int findOwnerIndex(int id) const;
    int findPropertyIndex(int id) const;
    int findTenantIndex(int id) const;
    int findAgreementIndex(int id) const;

    // Add helpers
    void addOwner();
    void addProperty();
    void addTenant();

    // Display helpers
    void displayOwners() const;
    void displayProperties() const;
    void displayTenants() const;
    void displayAgreements() const;

    friend class FileManager;

public:
    PropertySystem();

    void addRecord();
    void displayRecords() const;
    void searchRecord() const;
    void updateRecord();
    void deleteRecord();
    void processTransaction();
    void report() const;
    void saveNow() const;
    void loadData();
    void saveLoadMenu();
};

#endif
