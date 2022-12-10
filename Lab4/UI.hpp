//
//  UI.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 02/12/2022.
//

#ifndef UI_hpp
#define UI_hpp

#include "utils.hpp"
#include "menus.hpp"
#include "vacationParkAPI.hpp"
#include <iostream>
#include <regex>
#include <typeindex>
#include <map>
#include <unordered_map>
using namespace std;

const regex nameRegex("[a-zA-Z]+");
const regex addressRegex("[a-zA-Z0-9 ]+");
const regex stringRegex("[a-zA-Z0-9/:]+ *");

namespace owner{
void accessAsOwner(VacationPark& vp);
void createPark(VacationPark& vp);
void editPark(VacationPark& vp);
void editParkService(Park* park);
Park* getPark(VacationPark& vp, string displayText, int* index=nullptr);
void deletePark(VacationPark& vp);
void createAccomodation(VacationPark& vp);
map<int, void*>* getAccomodationDetails(VacationPark& vp, ownerAPI::ACC_TYPE* type, ownerAPI::ACC_TYPE* typeRet=nullptr);
void editAccomodation(VacationPark& vp);
void deleteAccomodation(VacationPark& vp);
Accomodation* getAccomodation(VacationPark& vp, string displayText, ownerAPI::ACC_TYPE* type=nullptr, int* parkIndex=nullptr, int* accomodationIndex=nullptr);
bool existParks(VacationPark& vp);
}

namespace customer{
void accessAsCustomer(VacationPark& vp);
Customer* loginCustomer(string& username, VacationPark& vp);
void registerCustomer(VacationPark& vp);
bool getCustomerDetails(VacationPark& vp,string& name, string& address, string& email);
void editCustomer(Customer*& customer, VacationPark& vp);
void createBooking(VacationPark& vp, Customer* customer);
}

namespace general{
template<typename T, typename U> int editFeature(string textDisplay, T object, U opt, bool (*func)(T, string, U), const regex re = regex{});
map<int, void*>* userPrompt(map<int, tuple<type_index, string>>& prompts);
}

#endif /* UI_hpp */
