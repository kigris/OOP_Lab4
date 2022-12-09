//
//  utils.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#include "utils.hpp"

// Get user choice
int getUserChoice(int min) {
    // Get user input
    string input;
    getline(cin, input);
    // Convert user input to integer
    int choice = -1;
    stringstream ss(input);
    // Try to read an integer
    if (ss >> choice) {
        // Check if user input is within range
        if (choice >= min) {
            return choice;
        }
    }
    // If input is invalid, return -1
    return -1;
}

// Get user choice
int getUserChoice(int min, int max) {
    // Get user input
    string input;
    getline(cin, input);
    // Convert user input to integer
    int choice = -1;
    stringstream ss(input);
    // Try to read an integer
    if (ss >> choice) {
        // Check if user input is within range
        if (choice >= min && choice <= max) {
            return choice;
        }
    }
    // If input is invalid, return -1
    return -1;
}
