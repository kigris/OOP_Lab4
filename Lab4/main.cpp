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
#include "fileManagement.hpp"
using namespace std;

int main(int argc, const char * argv[]){
    VacationPark vacationPark("Wonderland Park", "Avenue 52, 1020, Oklahoma, US");

    // Main loop
    bool exit = false;
    while (!exit) {
        // Display main menu
        menus::displayMainMenu();
        // Get user choice
        auto choice = getUserChoice(1, 6);
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
                fileMngmt::fileManagement(vacationPark);
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
