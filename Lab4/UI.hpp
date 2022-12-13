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
#include "fileManagement.hpp"
#include <unordered_map>
using namespace std;

const regex nameRegex("[a-zA-Z]+");
const regex addressRegex("[a-zA-Z0-9 ]+");
const regex stringRegex("[a-zA-Z0-9/:]+ *");
const int BOOKING_ID_LENGTH{8};

// Enumeration for main menu options
enum class MainMenuOption {
    ACCESS_AS_OWNER = 1,
    ACCESS_AS_EMPLOYEE = 2,
    ACCESS_AS_CUSTOMER = 3,
    FILE_MANAGEMENT = 4,
    EXIT = 5
};

// Enumeration for file management menu options
enum class FileManagementOption {
    STORE_DATA = 1,
    LOAD_DATA = 2,
    DELETE_DATA = 3,
    EXIT = 4
};

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
void registerCustomer(VacationPark& vp, bool employeeMode=false);
bool getCustomerDetails(VacationPark& vp,string& name, string& address, string& email, bool employeeMode=false);
void editCustomer(Customer*& customer, VacationPark& vp, bool employeeMode=false);
void createBooking(VacationPark& vp, Customer* customer, bool employeeMode=false);
map<int, tuple<Accomodation*, Park*>>* filterAccomodations(map<int, void*>* args, VacationPark& vp, Park* park=nullptr);
string generateBookingID(Customer* customer);
void editBookings(VacationPark& vp, Customer* customer, bool employeeMode=false);
bool existBookings(VacationPark& vp, Customer* customer);
Booking* getBookings(VacationPark& vp, Customer* customer, string displayText, int* index=nullptr);
void addAccomodation(Booking* booking, VacationPark& vp, bool employeeMode=false);
void removeAccomodation(Booking* booking, VacationPark& vp, bool employeeMode=false);
Accomodation* getAccomodationFiltered(VacationPark& vp, Park* p=nullptr, Booking* booking=nullptr, bool employeeMode=false);
void bookServices(Booking* booking, VacationPark& vp, bool employeeMode=false);
void loginCustomerMenu(VacationPark& vp);
}

namespace employee{
void accessAsEmployee(VacationPark& vp);
Customer* getCustomer(VacationPark& vp, string displayText, int* index=nullptr);
void editCustomer(VacationPark& vp);
void deleteCustomer(VacationPark& vp);
void createBooking(VacationPark& vp);
void editBooking(VacationPark& vp);
void deleteBooking(VacationPark& vp);
}

namespace general{
template<typename T, typename U> int editFeature(string textDisplay, T object, U opt, bool (*func)(T, string, U), const regex re = regex{});
map<int, void*>* userPrompt(map<int, tuple<type_index, string>>& prompts);
}

namespace fileMngmt{
void fileManagement(VacationPark& vp);
string& getSaveName(int* countSaves=nullptr);
}

#endif /* UI_hpp */
