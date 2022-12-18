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
    // Intro part, get details for vacation park object
    cout<<"Welcome to the management system of a vacation park!"<<endl;
    cout<<"Please enter the name of the vacation park: ";
    string vpName;
    getline(cin, vpName);
    // While loop to get a valid name, waiting for the user to press Enter
    while(!regex_match(vpName, nameRegex)){
        cout<<"Error: Invalid name..."<<endl;
        waitForEnter();
        cout<<"Please enter the name of the vacation park: ";
        getline(cin, vpName);
    }
    // Get the address of the park
    cout<<"Please enter the address of the vacation park: ";
    string vpAddress;
    getline(cin, vpAddress);
    // While loop to get a valid address, waiting for the user to press Enter
    while(!regex_match(vpAddress, addressRegex)){
        cout<<"Error: Invalid address..."<<endl;
        waitForEnter();
        cout<<"Please enter the address of the vacation park: ";
        getline(cin, vpAddress);
    }
    // Get the VAT of the park
    cout<<"Please enter the VAT of the vacation park: ";
    int vpVAT = getUserChoice(0);
    // While loop to get a valid VAT, waiting for the user to press Enter
    while(vpVAT==-1){
        cout<<"Error: Invalid VAT..."<<endl;
        waitForEnter();
        cout<<"Please enter the VAT of the vacation park: ";
        vpVAT = getUserChoice(0);
    }
    // Create the vacation park object
    VacationPark vacationPark(vpName, vpAddress, vpVAT);
    
    // Main menu loop
    bool exit = false;
    while (!exit) {
        // Display main menu
        menus::displayMainMenu(vpName);
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
            case MainMenuOption::VIEW_DATA:
                general::viewData(vacationPark);
                break;
            case MainMenuOption::EXIT:
                exit = true;
                break;
            default:{
                cout<<"Error: Invalid option..."<<endl;
                waitForEnter(true);
                break;
            }
        }
    }
    //    testCreationAndDeletionParks(500);
    return 0;
}
