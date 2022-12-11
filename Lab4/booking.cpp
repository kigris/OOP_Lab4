//
//  booking.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//
#include <string>
using std::string;
#include "booking.hpp"

vector<string> Booking::g_IDs = {};

Booking::Booking(string id, Customer* customer, bool activityPass, bool bicycleRent, bool swimmingPass){
    if(!setID(id)){
        throw std::invalid_argument("Duplicate ID");
    }
    setCustomer(customer);
    setActivityPass(activityPass);
    setBicycleRentPass(bicycleRent);
    setSwimmingPass(swimmingPass);
};

Booking::Booking(string id, Customer* customer, vector<Accomodation*> accomodations, bool activityPass, bool bicycleRent, bool swimmingPass){
    if(!setID(id)){
        throw std::invalid_argument("Duplicate ID");
    }
    setCustomer(customer);
    setAccomodations(accomodations);
    setActivityPass(activityPass);
    setBicycleRentPass(bicycleRent);
    setSwimmingPass(swimmingPass);
};

Booking::~Booking(){
    // We remove the ID from the list of IDs used
    g_IDs.erase(remove(g_IDs.begin(), g_IDs.end(), m_ID), g_IDs.end());
    // Release all accomodations
    for(auto a : m_Accomodations)
        a->release();
}

bool Booking::setID(string id){
    // Check that the id is not taken
    for(string i : g_IDs)
        if(i==id)
            return false;
    // We remove the current one
    g_IDs.erase(remove(g_IDs.begin(), g_IDs.end(), m_ID), g_IDs.end());
    // If the id given is not found
    m_ID = id;
    // We add the id given to the IDs taken
    g_IDs.push_back(id);
    return true;
}
void Booking::setCustomer(Customer* customer) {m_Customer = customer;}
void Booking::setAccomodations(vector<Accomodation*> accomodations) {m_Accomodations = accomodations;}
void Booking::setActivityPass(bool activityPass){m_ActivityPass = activityPass;}
void Booking::setSportsPass(bool sportsPass){m_SportsPass=sportsPass;};
void Booking::setBicycleRentPass(bool bicycleRent){m_BicyleRentPass = bicycleRent;}
void Booking::setSwimmingPass(bool swimmingPass){m_SwimmingPass = swimmingPass;}
