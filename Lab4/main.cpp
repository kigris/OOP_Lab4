//
//  main.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/11/2022.
//

#include <iostream>
#include "luxuryLevel.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    LuxuryLevel lx;
    lx.getBBQ();
    std::cout<<lx.getBBQ();
    return 0;
}
