#include "FileManager.h"
#include "PropertySystem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#define MAKE_DIR(d) _mkdir(d)
#else
#include <sys/stat.h>
#define MAKE_DIR(d) mkdir(d, 0777)
#endif

namespace {
    void ensureDirectory() {
        MAKE_DIR("Data");
    }

    std::vector<std::string> splitLine(const std::string& line) {
        std::vector<std::string> parts;
        std::stringstream ss(line);
        std::string part;
        while (std::getline(ss, part, '|')) {
            parts.push_back(part);
        }
        return parts;
    }
}

void FileManager::save(const PropertySystem& s) {
    ensureDirectory();

    // 1. Save Owners
    std::ofstream outOwner("Data/owners.txt");
    if (outOwner.is_open()) {
        for (const auto& o : s.owners) {
            outOwner << o.getId() << "|" << o.getName() << "|" << o.getPhone() << "\n";
        }
        outOwner.close();
    }

    // 2. Save Properties
    std::ofstream outProp("Data/properties.txt");
    if (outProp.is_open()) {
        for (const auto& p : s.properties) {
            outProp << p.getId() << "|" << p.getAddress() << "|" << p.getType() << "|"
                    << p.getRent() << "|" << p.getStatus() << "|" << p.getOwnerId() << "\n";
        }
        outProp.close();
    }

    // 3. Save Tenants
    std::ofstream outTenant("Data/tenants.txt");
    if (outTenant.is_open()) {
        for (const auto& t : s.tenants) {
            outTenant << t.getId() << "|" << t.getName() << "|" << t.getPhone() << "\n";
        }
        outTenant.close();
    }

    // 4. Save Agreements
    std::ofstream outAgreements("Data/agreements.txt");
    if (outAgreements.is_open()) {
        for (const auto& a : s.agreements) {
            outAgreements << a.getId() << "|" << a.getPropertyId() << "|" << a.getTenantId() << "|"
                          << a.getMonthlyRent() << "|" << a.getDurationMonths() << "|" << a.getStatus() << "\n";
        }
        outAgreements.close();
    }
}

void FileManager::load(PropertySystem& s) {
    s.owners.clear();
    s.properties.clear();
    s.tenants.clear();
    s.agreements.clear();

    std::string line;

    // 1. Load Owners
    std::ifstream inOwner("Data/owners.txt");
    while (inOwner && std::getline(inOwner, line)) {
        if (line.empty()) continue;
        auto tokens = splitLine(line);
        if (tokens.size() == 3) {
            s.owners.push_back(Owner(std::stoi(tokens[0]), tokens[1], tokens[2]));
        }
    }

    // 2. Load Properties
    std::ifstream inProp("Data/properties.txt");
    while (inProp && std::getline(inProp, line)) {
        if (line.empty()) continue;
        auto tokens = splitLine(line);
        if (tokens.size() == 6) {
            s.properties.push_back(Property(std::stoi(tokens[0]), tokens[1], tokens[2],
                                            std::stod(tokens[3]), std::stoi(tokens[5]), tokens[4]));
        }
    }

    // 3. Load Tenants
    std::ifstream inTenant("Data/tenants.txt");
    while (inTenant && std::getline(inTenant, line)) {
        if (line.empty()) continue;
        auto tokens = splitLine(line);
        if (tokens.size() == 3) {
            s.tenants.push_back(Tenant(std::stoi(tokens[0]), tokens[1], tokens[2]));
        }
    }

    // 4. Load Agreements
    std::ifstream inAgreements("Data/agreements.txt");
    int maxId = 0;
    while (inAgreements && std::getline(inAgreements, line)) {
        if (line.empty()) continue;
        auto tokens = splitLine(line);
        if (tokens.size() == 6) {
            int id = std::stoi(tokens[0]);
            s.agreements.push_back(RentalAgreement(id, std::stoi(tokens[1]), std::stoi(tokens[2]),
                                                  std::stod(tokens[3]), std::stoi(tokens[4]), tokens[5]));
            if (id > maxId) maxId = id;
        }
    }
    s.nextAgreementId = maxId + 1;
}
