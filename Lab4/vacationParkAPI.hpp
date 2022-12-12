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
#include "hotelRoom.hpp"
#include "cabin.hpp"
#include <vector>
#include <iostream>
#include <regex>
#include <typeindex>
#include <map>
#include <string>
using namespace std;

#ifdef DEBUG
    #include <cassert>
#endif

// Enumeration for main menu options
enum class PARK_EDIT_OPT {
    NAME = 1,
    ADDRESS = 2,
    ACCESS_AS_CUSTOMER = 3,
    FILE_MANAGEMENT = 4,
    EXIT = 5
};

// Container to wrap a generic value
template <typename T> struct Value {
    Value(T input){value=input;}
    T value;
};

namespace ownerAPI {
enum class ACC_TYPE {
    HOTELROOM = 1,
    CABIN = 2
};

bool findPark(vector<unique_ptr<Park>>& parks, string parkName);
bool createPark(VacationPark& vp, string name, string address, Service* service);
Service* createService(map<int,void*>* args);
bool updateParkFeature(Park* park, string input, PARK_EDIT_OPT opt);
bool updateParkServices(Park* park, bool input[]);
bool deletePark(int index, VacationPark& vp);
Park* getPark(VacationPark& vp, int index);
Accomodation* getAccomodation(VacationPark& vp, int parkIndex, int accomodationIndex);
bool findAccomodation(vector<unique_ptr<Park>>& parks, int id);
bool createAccomodation(vector<Accomodation*>& accomodations, map<int,void*>* args, ACC_TYPE type);
bool updateAccomodation(Accomodation* accomodation, map<int,void*>* args, ACC_TYPE type);
bool deleteAccomodation(int parkIndex, int accomodationIndex, VacationPark& vp);
}

namespace customerAPI{
bool createCustomer(VacationPark& vp, string name, string address, string mail);
bool findCustomer(vector<unique_ptr<Customer>>& customers, string customerName);
bool findCustomer(vector<unique_ptr<Customer>>& customers, string customerName, Customer*& customer);
bool updateCustomer(Customer*& customer, string name, string address, string mail);
bool findBooking(vector<unique_ptr<Booking>>& bookings, string id);
bool createBooking(VacationPark& vp, Customer* customer, Accomodation* accomodation, string id, bool activityPass, bool bicycleRent, bool swimmingPass);
bool updateBooking(Booking* booking, Accomodation* accomodation);
bool removeAccFromBooking(Booking* booking, Accomodation* accomodation);
Park* getBookingPark(VacationPark& vp, Booking* booking);
bool setBookingServices(Booking* booking, bool passes[4]);
}

namespace employeeAPI {
bool deleteCustomer(int index, VacationPark& vp);
bool deleteBooking(int index, VacationPark& vp);
}

#endif /* vacationParkAPI_hpp */
