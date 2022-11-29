//
//  booking.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//
#include <string>
using std::string;
#include "booking.hpp"

vector<int> Booking::g_IDs = {};

Booking::Booking(int id, Customer* customer, vector<Accomodation*> accomodations, bool activityPass, bool bicycleRent, bool swimmingPass){
    if(!setID(id)){
        throw std::invalid_argument("Duplicate ID");
    }
    setCustomer(customer);
    setAccomodations(accomodations);
    setActivityPass(activityPass);
    setBicycleRent(bicycleRent);
    setSwimmingPass(swimmingPass);
};

Booking::~Booking(){
    for(auto a : m_Accomodations)
        delete a;
}

bool Booking::setID(int id){
    // Check that the id is not taken
    for(int i : g_IDs)
        if(i==id)
            return false;
    // If the id given is not found
    m_ID = id;
    // We add the id given to the IDs taken
    g_IDs.push_back(id);
    return true;
}
void Booking::setCustomer(Customer* customer) {m_Customer = customer;}
void Booking::setAccomodations(vector<Accomodation*> accomodations) {m_Accomodations = accomodations;}
void Booking::setActivityPass(bool activityPass){m_ActivityPass = activityPass;}
void Booking::setBicycleRent(bool bicycleRent){m_BicyleRent = bicycleRent;}
void Booking::setSwimmingPass(bool swimmingPass){m_SwimmingPass = swimmingPass;}
