//
//  main.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/11/2022.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include "luxuryLevel.hpp"
#include "customer.hpp"
#include "park.hpp"
#include "parkCompany.hpp"
#include "customerAPI.hpp"
using namespace std;

void clearCin();
byte login();
bool menu(byte userType);
void customerSignUp();
bool customerLogin(Customer* customer);
bool getAnswer(string*& matches, regex reg);
int getDigitAnswer(string*& matches, int* errorCode);
void displayText(char* textDisplay);
template<typename T> void displayError(T answer, T error, char* errorDisplay);

constexpr byte ERROR_BYTE{0x0};
constexpr byte COSTUMER_BYTE{0x1};
constexpr byte EMPLOYEE_BYTE{0x2};
constexpr byte OWNER_BYTE{0x3};
constexpr byte EXIT_BYTE{0x4};
const regex regDigit(R"(^\d+ ?)");
const regex regString(R"(\w+ ?)");
ParkCompany parkComp("Wonderland Park", "Avenue 52, 1020, Oklahoma, US");

int main(int argc, const char * argv[]){
    byte userType{ERROR_BYTE};

    // As long as we don't get a valid response
    while(userType==ERROR_BYTE){
        // We loop until we get one
        userType = login();
        displayError<byte>(userType, ERROR_BYTE, (char*)"Error: You must enter a valid option");
        if(userType==EXIT_BYTE)
            break;
        
        // If we did not get the exit byte, means we logged in
        if(userType!=ERROR_BYTE){
            bool stayMenu{true};
            // While we want to stay into the menu
            while(stayMenu){
                // Check the submenu input to see if we wannt to stay or go back to login
                stayMenu=menu(userType);
            }
            // Go back to the login screen by setting the usertype to error byte
            userType=ERROR_BYTE;
        }
    }
}

template<typename T> void displayError(T answer, T error, char* errorDisplay){
    if(answer==error){
        cout<<endl<<errorDisplay<<"\nPress 'Enter' to continue..."<<endl;
        clearCin();
    }
}

void displayText(char* textDisplay){
    cout<<endl<<textDisplay<<"\nPress 'Enter' to continue..."<<endl;
    clearCin();
}

byte login(){
    cout << "Welcome to the Vacation Park Pause!\nWhat are you?"<<endl;
    cout << "\t1. Costumer\n\t2. Employee\n\t3. Owner\n";
    cout << "\t0. Exit\n";
    
    // Getting the answer
    uint8_t answerNum=0;
    string* matches;
    int errorCode{0};
    answerNum = getDigitAnswer(matches, &errorCode);
    delete[] matches; // Free the pointer of the matches
    if(!errorCode){
        // We look at the answer we get
        switch(answerNum){
                // Customer case
            case 1:
                return COSTUMER_BYTE;
                // Employee case
            case 2:
                return EMPLOYEE_BYTE;
                // Owner case
            case 3:
                return OWNER_BYTE;
            case 0:
                return EXIT_BYTE;
        }
    }
    return ERROR_BYTE;
}

void customerMenu() {
    cout<<"Enter your username: ";
    string* matches;
    bool hasAnswer = getAnswer(matches, regString);
    if(!hasAnswer){
        displayText((char*)"Error: Username invalid");
        return;
    }
    vector<Customer*> customers = parkComp.getCustomers();
    Customer* customer;
    bool existCustomer = findCustomer(customers, matches[0], customer);
    if(existCustomer){
        // While we want to stay into the menu
        bool stayMenu{true};
        while(stayMenu){
            // Check the submenu input to see if we wannt to stay or go back to login
            stayMenu=customerLogin(customer);
        }
    } else{
        displayText((char*)"Error: Username not found");
    }
}

bool menu(byte userType){
    switch (userType) {
        case COSTUMER_BYTE:{
            cout<<"\nCostumer Menu:"<<endl;
            cout << "\t1. Login\n\t2. Sign up\n";
            cout << "\t0. Go back to main menu\n";
            // Getting the answer
            uint8_t answerNum=0;
            string* matches;
            int errorCode{0};
            answerNum = getDigitAnswer(matches, &errorCode);
            delete[] matches;
            if(!errorCode){
                switch (answerNum) {
                    case 1:{
                        customerMenu();
                        break;
                    }
                    case 2:
                        customerSignUp();
                        break;
                    case 0:{
                        displayText((char*)"Returning to main menu...");
                        return false;
                    }
                    default:
                        break;
                }
            }
            break;
        }
        case EMPLOYEE_BYTE:
            cout<<"Employee";
            break;
        case OWNER_BYTE:
            cout<<"Owner";
            break;
    }
    return true;
}

void customerSignUp(){
    string* matches;
    cout<<"Enter your username: ";
    bool hasAnswer = getAnswer(matches, regString);
    if(!hasAnswer){
        displayText((char*)"Error: Not a valid username");
        return;
    }
    string name = matches[0];
    delete[] matches;
    
    // Check the name is not duplicated
    vector<Customer*> customers = parkComp.getCustomers();
    Customer* customer;
    bool duplicateCustomer = findCustomer(customers, name, customer);
    if(duplicateCustomer){
        displayText((char*)"Error: Duplicated username");
        return;
    }
    
    cout<<"Enter your address: ";
    hasAnswer = false;
    hasAnswer = getAnswer(matches, regString);
    if(!hasAnswer){
        displayText((char*)"Error: Not a valid address");
        return;
    }
    string address = matches[0];
    delete[] matches;
    
    cout<<"Enter your mail: ";
    hasAnswer = false;
    hasAnswer = getAnswer(matches, regString);
    if(!hasAnswer){
        displayText((char*)"Error: Not a valid mail");
        return;
    }
    string mail = matches[0];
    delete[] matches;
    
    Customer* c = new Customer(name, address, mail);
    customers.push_back(c);
    parkComp.setCustomers(customers);
    displayText((char*)"Customer created successfully!");
}

bool customerLogin(Customer* customer){
    string* matches;
    cout<<"\nWelcome "<<customer->getName()<<endl;
    cout<<"\tWhat do you want to do?\n\t\t1. Create booking\n\t\t2. Change Booking\n\t\t0. Go back to costumer menu"<<endl;
    int errorCode{0};
    uint8_t answerNum = getDigitAnswer(matches, &errorCode);
    if(!errorCode){
        switch (answerNum) {
            case 1:
                cout<<"Creating booking"<<endl;
                break;
            case 2:{
                cout<<"Changing booking"<<endl;
                break;
            }
            case 0:
                displayText((char*)"Returning to costumer menu...");
                return false;
        }
    }
    return true;
}

bool getAnswer(string*& matches, regex reg){
    // Getting the answer
    string answerStream;
    getline(cin, answerStream);
    // Checking if we get a number
    smatch m;
    if(regex_match(answerStream, m, reg)){
        // We initialize the matches pointer
        matches = new string[m.size()];
        int counter=0;
        for(auto i:m){
            matches[counter]=i;
            counter++;
        }
        return true;
    }

    return false;
}

int getDigitAnswer(string*& matches, int* errorCode){
    uint8_t answerNum=0;
    bool hasAnswer = getAnswer(matches, regDigit);
    // Checking if we get a number
    if(hasAnswer)
        answerNum=atoi(matches[0].c_str());
    else
        *errorCode=1;
    return answerNum;
}

//bool isNumber(const string& s){
//    // Iterate over each character of the string
//    for(const char& c:s)
//        // If it's not a digit
//        if(isdigit(c)==0)
//            // If it's not an empty space or endline
//            if(c!='\0' && c!=' ')
//                // Then the string it's not a number
//                return false;
//    return true;
//}

void clearCin(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
