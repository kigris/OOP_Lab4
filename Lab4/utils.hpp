//
//  utils.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#ifndef utils_hpp
#define utils_hpp

#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

// Wait for user to press Enter
inline void waitForEnter(bool newLineAfter=false) {
    if(newLineAfter)
        cout << "Press 'Enter' to continue..." << endl;
    else
        cout << "Press 'Enter' to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// Print tab function
inline string tabSpace(){
    return "\t";
}

inline string convToLower(string str){
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
    return str;
}

int getUserChoice(int min);
int getUserChoice(int min, int max);
#endif /* utils_hpp */
