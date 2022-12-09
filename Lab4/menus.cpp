//
//  menus.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#include "menus.hpp"

namespace menus{

void displayCustomerLoginMenu(string name) {
    cout << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "Welcome " << name << "! What do you want to do?" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "1. Edit customer data" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "2. Create booking" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "3. Search for bookings" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "4. Book accommodations" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "5. Edit bookings" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "6. Log out" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "Enter your choice: ";
}

// Display main menu
void displayMainMenu() {
    cout << "Welcome to the Vacation Park Management System" << endl;
    cout << tabSpace();
    cout << "1. Access as Owner" << endl;
    cout << tabSpace();
    cout << "2. Access as Employee" << endl;
    cout << tabSpace();
    cout << "3. Access as Customer" << endl;
    cout << tabSpace();
    cout << "4. File management" << endl;
    cout << tabSpace();
    cout << "5. Exit" << endl;
    cout << tabSpace();
    cout << "Enter your choice: ";
}

void displayCustomerMenu() {
    cout << endl;
    cout << tabSpace() << tabSpace();
    cout << "--- Customer ---" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "1. Register" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "2. Login" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "3. Back" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "Enter your choice: ";
}

void displayOwnerMenu() {
    cout << endl;
    cout << tabSpace() << tabSpace();
    cout << "--- Owner ---" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "1. Create Park" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "2. Edit Park" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "3. Delete Park" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "4. Create Accomodation" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "5. Edit Accomodation" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "5. Delete Accomodation" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "Enter your choice: ";
}

}

