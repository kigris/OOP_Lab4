//
//  customerAPI.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 29/11/2022.
//

#ifndef vacationParkAPI_hpp
#define vacationParkAPI_hpp

#include "vacationPark.hpp"
#include "utils.hpp"
#include <vector>
#include <iostream>
#include <regex>
#include <string>
using namespace std;
using namespace std::placeholders;

// Enumeration for main menu options
enum class PARK_EDIT_OPT {
    NAME = 1,
    ADDRESS = 2,
    ACCESS_AS_CUSTOMER = 3,
    FILE_MANAGEMENT = 4,
    EXIT = 5
};
namespace customerAPI{
bool createCustomer(VacationPark& vp, string name, string address, string mail);
bool findCustomer(vector<unique_ptr<Customer>>& customers, string customerName);
bool findCustomer(vector<unique_ptr<Customer>>& customers, string customerName, Customer*& customer);
bool updateCustomer(Customer*& customer, string name, string address, string mail);

}
namespace ownerAPI {
bool findPark(vector<unique_ptr<Park>>& parks, string parkName);
bool createPark(VacationPark& vp, string name, string address);
bool updateParkFeature(Park* park, string input, PARK_EDIT_OPT opt);
bool updateParkMultipleFeatures(Park* park, bool input[]);
bool deletePark(int index, VacationPark& vp);
Park* getPark(VacationPark& vp, int index);
bool findAccomodation(vector<unique_ptr<Park>>& parks, int id);
}

#endif /* vacationParkAPI_hpp */
