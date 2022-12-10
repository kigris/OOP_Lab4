//
//  menus.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 01/12/2022.
//

#ifndef menus_hpp
#define menus_hpp

#include <stdio.h>
#include <iostream>
#include "customer.hpp"
#include "vacationPark.hpp"
#include "utils.hpp"
using namespace std;

namespace menus{

void displayCustomerMenu();
void displayMainMenu();
void displayCustomerLoginMenu(string name);

namespace owner{
int (&displayOwnerMenu())[2];
int (&parkUpdateMenu())[2];
}

}
#endif /* menus_hpp */
