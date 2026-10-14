#ifndef PROPERTY_H
#define PROPERTY_H

#include "Displayable.h"
#include <string>

class Property : public Displayable {
private:
    int propertyId;
    std::string address;
    std::string type;
    std::string status;
    double rent;
    int ownerId;

public:
    Property();
    Property(int id, const std::string& propertyAddress, const std::string& propertyType, 
             double monthlyRent, int propertyOwnerId, const std::string& propertyStatus = "Available");

    int getId() const;
    std::string getAddress() const;
    std::string getType() const;
    double getRent() const;
    std::string getStatus() const;
    int getOwnerId() const;

    bool isAvailable() const;
    void updateDetails(const std::string& propertyAddress, const std::string& propertyType, double monthlyRent);
    void setStatus(const std::string& newStatus);
    void display() const override;
};

#endif
