//
//  menus.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#include "menus.hpp"

namespace menus{

int (&displayCustomerLoginMenu(string name))[2] {
    cout << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "Welcome " << name << "! What do you want to do?" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "1. Edit customer data" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "2. Create booking" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "3. Change booking" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "4. Log out" << endl;
    cout << tabSpace() << tabSpace() << tabSpace() << tabSpace() << tabSpace();
    cout << "Enter your choice: ";
    static int choicesRange[2]{1,4};
    return choicesRange;
}

int (&displayBookingMenu(string bookingID))[2] {
    cout << endl;
    cout << tabSpace();
    cout << "Editing booking with ID " << bookingID << endl;
    cout << tabSpace() << "What do you want to do?" << endl;
    cout << tabSpace() << tabSpace() <<"1. Add accomodations to bookings" <<endl;
    cout << tabSpace() << tabSpace() <<"2. Remove accomodations from bookings" <<endl;
    cout << tabSpace() << tabSpace() <<"3. Book park services" <<endl;
    cout << tabSpace() << tabSpace() <<"4. Exit"<<endl;
    cout << tabSpace() << tabSpace() << "Enter your choice: ";
    static int choicesRange[2]{1,4};
    return choicesRange;
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

namespace owner{

int (&displayOwnerMenu())[2] {
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
    cout << "6. Delete Accomodation" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "7. Go back to main menu" << endl;
    cout << tabSpace() << tabSpace() << tabSpace();
    cout << "Enter your choice: ";
    static int choicesRange[2]{1,7};
    return choicesRange;
}

int (&parkUpdateMenu())[2]{
    cout << endl <<"Want you want to do?"<<endl;
    cout << tabSpace() << "1. Update name"<<endl;
    cout << tabSpace() << "2. Update address"<<endl;
    cout << tabSpace() << "3. Update services"<<endl;
    cout << tabSpace() << "4. Exit"<<endl;
    cout << tabSpace() << "Enter your choice: ";
    static int choicesRange[2]{1,4};
    return choicesRange;
}

}

}

