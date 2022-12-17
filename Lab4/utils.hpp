//
//  utils.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#ifndef utils_hpp
#define utils_hpp

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;


/// Wait for user to press Enter
inline void waitForEnter(bool newLineAfter=false) {
    // If a new line is needed after the message
    if(newLineAfter)
        cout << "Press 'Enter' to continue..." << endl; // print it
    else
        cout << "Press 'Enter' to continue...";
    // Clear the input buffer and wait for user to press Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
}

/// Check if the user choice is an error
/// - Parameters:
///   - choice: integer that represents the user choice
///   - errorChoice: integer that represents the error choice
///   - message: message to be displayed if the user choice is an error
inline bool checkError(int choice, int errorChoice, string message){
    // If the user choice is an error
    if(errorChoice == choice){
        // Display the error message
        cout << message << endl;
        waitForEnter(); // wait for user to press Enter
        return true;
    }
    return false;
}

/// Display an error message
/// - Parameter message: message to be displayed
inline void displayError(string message){
    // Display the error message
    cout << message << endl;
    waitForEnter(); // wait for user to press Enter
    
}

/// Display a tabspace
inline string tabSpace(){
    return "\t";
}

/// Convert a string to lowercase
/// - Parameter str: string to be converted
inline string convToLower(string str){
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
    return str;
}

/// Get user choice
/// - Parameter min: minimum value accepted
int getUserChoice(int min);

/// Get user choice
/// - Parameters:
///   - min: minimum value accepted
///   - max: maximum value accepted
int getUserChoice(int min, int max);

/// Generate a random ID
/// - Parameters:
///   - len: length of the ID
///   - input: string to be used as the source of the first half of the hash
string randIDGen(const int len, const string& input);
#endif /* utils_hpp */
