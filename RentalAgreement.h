#ifndef RENTALAGREEMENT_H
#define RENTALAGREEMENT_H

#include "Displayable.h"
#include <string>

class RentalAgreement : public Displayable {
private:
    int agreementId;
    int propertyId;
    int tenantId;
    double monthlyRent;
    int durationMonths;
    std::string status;

public:
    RentalAgreement();
    RentalAgreement(int aId, int pId, int tId, double rent, int months, const std::string& s = "Active");

    int getId() const;
    int getPropertyId() const;
    int getTenantId() const;
    double getMonthlyRent() const;
    int getDurationMonths() const;
    std::string getStatus() const;

    double calculateRent() const;
    void terminate();
    void display() const override;
};

#endif
