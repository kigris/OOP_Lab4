//
//  main.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/11/2022.
//

#include <iostream>
#include <string>
#include <regex>
#include "utils.hpp"
#include "menus.hpp"
#include "UI.hpp"
#include "unitTesting.hpp"
using namespace std;

// Enumeration for main menu options
enum class MainMenuOption {
    ACCESS_AS_OWNER = 1,
    ACCESS_AS_EMPLOYEE = 2,
    ACCESS_AS_CUSTOMER = 3,
    FILE_MANAGEMENT = 4,
    EXIT = 5
};

// Enumeration for file management menu options
enum class FileManagementOption {
    STORE_CURRENT_INFORMATION = 1,
    LOAD_INFORMATION = 2,
    EXIT = 3
};


int main(int argc, const char * argv[]){
    VacationPark vacationPark("Wonderland Park", "Avenue 52, 1020, Oklahoma, US");

    // Main loop
    bool exit = false;
    while (!exit) {
        // Display main menu
        menus::displayMainMenu();
        // Get user choice
        auto choice = getUserChoice(1, 5);
        // Convert user choice to MainMenuOption enumerator
        MainMenuOption option = static_cast<MainMenuOption>(choice);
        // Process user choice
        switch (option) {
            case MainMenuOption::ACCESS_AS_OWNER:
                owner::accessAsOwner(vacationPark);
                break;
            case MainMenuOption::ACCESS_AS_EMPLOYEE:
                employee::accessAsEmployee(vacationPark);
                break;
            case MainMenuOption::ACCESS_AS_CUSTOMER:{
                customer::accessAsCustomer(vacationPark);
            }
                break;
            case MainMenuOption::FILE_MANAGEMENT:
//                fileManagement();
                break;
            case MainMenuOption::EXIT:
                exit = true;
                break;
            default:{
                cout<<"Invalid option..."<<endl;
                waitForEnter(true);
            }
            break;
        }
    }
//    testCreationAndDeletionParks(500);
    return 0;
}
