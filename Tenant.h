#ifndef TENANT_H
#define TENANT_H

#include "Displayable.h"
#include <string>

class Tenant : public Displayable {
private:
    int tenantId;
    std::string name;
    std::string phone;

public:
    Tenant();
    Tenant(int id, const std::string& tenantName, const std::string& phoneNumber);

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;

    void updateDetails(const std::string& tenantName, const std::string& phoneNumber);
    void display() const override;
};

#endif
