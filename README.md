# Apartment Rental Management System (C++)

A clean, modular Object-Oriented C++ project designed for college coursework and GitHub portfolios.

## Features
- **Object-Oriented Programming (OOP):** Encapsulation, inheritance, polymorphism with `Displayable` interface.
- **CRUD Operations:** Add, view, search, update, and delete records for Owners, Properties, Tenants, and Rental Agreements.
- **Transaction Processing:** Create and terminate rental agreements with automated status updates.
- **File Persistence:** Text file-based storage inside a `Data/` directory.

## How to Compile & Run

### Using g++ (Terminal / Command Prompt):
```bash
g++ -std=c++11 main.cpp PropertySystem.cpp FileManager.cpp Owner.cpp Property.cpp Tenant.cpp RentalAgreement.cpp -o RentalSystem
./RentalSystem
```

### On Windows:
```cmd
g++ -std=c++11 main.cpp PropertySystem.cpp FileManager.cpp Owner.cpp Property.cpp Tenant.cpp RentalAgreement.cpp -o RentalSystem.exe
RentalSystem.exe
```
