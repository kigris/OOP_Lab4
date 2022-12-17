//
//  utils.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#include "utils.hpp"

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

string randIDGen(const int len, const string& input) {
    // Use the input string as the source of the first half of the hash
    string alphanum =  input;
    // Capitalize the input string
    transform(alphanum.begin(), alphanum.end(), alphanum.begin(), ::toupper);
    string hash_i; // Intermediate hash
    hash_i.reserve(len);
    for (int i = 0; i < (len*2); ++i) {
        // Get the first half of the hash
        char tmp = alphanum[rand() % alphanum.size()];
        if(isdigit(tmp)) // If picked up a number
            continue; // Skip it
        hash_i += tmp; // Otherwise, append it
    }
    
    static const char alphaChars[] ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < (len*3); ++i) {
        // Get the second half of the hash
        hash_i += alphaChars[rand() % (sizeof(alphaChars) - 1)];
    }
    
    string hash_f; // Final hash
    hash_f.reserve(len);
    for (int i = 0; i < len/2; ++i) {
        // Get the final hash
        hash_f += hash_i[rand() % (hash_i.size())];
    }
    static const char numChars[] ="0123456789";
    for (int i = 0; i < len/2; ++i) {
        // Get the final hash
        hash_f += numChars[rand() % (sizeof(numChars) - 1)];
    }
    return hash_f;
}
