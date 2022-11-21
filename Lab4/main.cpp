//
//  main.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/11/2022.
//

#include <iostream>
#include <string>
#include <sstream>
#include "luxuryLevel.hpp"
using namespace std;

void clearCin();
byte login();
bool isNumber(const string& s);
template<typename T> void displayError(T answer, T error, char* errorDisplay);

int main(int argc, const char * argv[]){
    byte userType{0x00};
    
    constexpr byte COSTUMER_BYTE{0x01};
    constexpr byte EMPLOYEE_BYTE{0x10};
    constexpr byte OWNER_BYTE{0x11};
    
    // As long as we don't get a valid response
    while(userType==(byte)0x00){
        // We loop until we get one
        userType = login();
        displayError<byte>(userType, (byte)0x00, (char*)"Error: You must enter a valid option");
    }
    
    // TODO
    switch (userType) {
        case COSTUMER_BYTE:
            cout<<"Costumer";
            break;
        case EMPLOYEE_BYTE:
            cout<<"Employee";
            break;
        case OWNER_BYTE:
            cout<<"Owner";
            break;
        default:
            break;
    }
}

template<typename T> void displayError(T answer, T error, char* errorDisplay){
    if(answer==error){
        cout<<endl<<errorDisplay<<"\nPress 'Enter' to continue..."<<endl;
        clearCin();
    }
}

byte login(){
    cout << "Welcome to the Vacation Park Pause!\nHow do you want to login?"<<endl;
    cout << "\t1. Costumer\n\t2. Employee\n\t3.Owner\n";
    
    // Getting the answer
    string answerStream;
    getline(cin, answerStream);
    uint8_t answerNum=0;
    // Checking if we get a number
    if(isNumber(answerStream))
        answerNum=atoi(answerStream.c_str());
    
    // We look at the answer we get
    switch(answerNum){
        // Customer case
        case 1:
            return (byte)0x01;
        // Employee case
        case 2:
            return (byte)0x10;
        // Owner case
        case 3:
            return (byte)0x11;
        // Invalid option case
        default:
            return (byte)0x00;
    }
}

bool isNumber(const string& s){
    // Iterate over each character of the string
    for(const char& c:s)
        // If it's not a digit
        if(isdigit(c)==0)
            // If it's not an empty space or endline
            if(c!='\0' && c!=' ')
                // Then the string it's not a number
                return false;
    return true;
}

void clearCin(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
