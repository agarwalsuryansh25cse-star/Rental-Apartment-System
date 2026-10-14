#ifndef OWNER_H
#define OWNER_H

#include "Displayable.h"
#include <string>

class Owner : public Displayable {
private:
    int ownerId;
    std::string name;
    std::string phone;

public:
    Owner();
    Owner(int id, const std::string& ownerName, const std::string& phoneNumber);

    int getId() const;
    std::string getName() const;
    std::string getPhone() const;

    void updateDetails(const std::string& ownerName, const std::string& phoneNumber);
    void display() const override;
};

#endif
