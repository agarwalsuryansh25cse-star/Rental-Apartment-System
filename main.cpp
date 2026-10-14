#include "PropertySystem.h"
#include <iostream>
#include <limits>

void showMenu() {
    std::cout << "\n=======================================\n";
    std::cout << "       APARTMENT RENTAL SYSTEM         \n";
    std::cout << "=======================================\n";
    std::cout << "1. Add Record\n";
    std::cout << "2. Display Records\n";
    std::cout << "3. Search Record\n";
    std::cout << "4. Update Record\n";
    std::cout << "5. Delete Record\n";
    std::cout << "6. Main Transaction / Rent Property\n";
    std::cout << "7. System Summary Report\n";
    std::cout << "8. Save / Load Data\n";
    std::cout << "9. Exit\n";
}

int getMenuChoice() {
    int choice;
    std::cout << "Enter your choice (1-9): ";
    if (std::cin >> choice) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1;
}

int main() {
    PropertySystem system;

    // Load initial data if files exist
    system.loadData();

    bool running = true;
    while (running) {
        showMenu();
        int choice = getMenuChoice();

        switch (choice) {
            case 1:
                system.addRecord();
                break;
            case 2:
                system.displayRecords();
                break;
            case 3:
                system.searchRecord();
                break;
            case 4:
                system.updateRecord();
                break;
            case 5:
                system.deleteRecord();
                break;
            case 6:
                system.processTransaction();
                break;
            case 7:
                system.report();
                break;
            case 8:
                system.saveLoadMenu();
                break;
            case 9:
                system.saveNow();
                std::cout << "Data saved. Thank you for using the system!\n";
                running = false;
                break;
            default:
                std::cout << "Invalid choice! Please enter a number between 1 and 9.\n";
                break;
        }
    }

    return 0;
}
