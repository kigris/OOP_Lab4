//
//  vacationPark.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#include "vacationPark.hpp"

vector<string> VacationPark::g_Names = {};

VacationPark::VacationPark(string name, string address){

}

VacationPark::VacationPark(string name, string address, vector<unique_ptr<Park>> parks, vector<unique_ptr<Customer>> customers, vector<unique_ptr<Booking>> bookings){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
    m_Parks = move(parks);
    m_Customers = move(customers);
    m_Bookings = move(bookings);
}

VacationPark::~VacationPark(){
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
}

bool VacationPark::setName(string name){
    // Check that the name is not taken
    for(string n : g_Names)
        if(n==name)
            return false;
    // If the name given is not found
    m_Name = name;
    // We add the name given to the names taken
    g_Names.push_back(name);
    return true;
}

void VacationPark::setVAT(string VAT) {
    m_VAT = VAT;
}

void VacationPark::setAddress(string address){
    m_Address = address;
}

void VacationPark::setParks(vector<unique_ptr<Park>> parks){
    m_Parks = move(parks);
}

void VacationPark::setCustomers(vector<unique_ptr<Customer>> customers){
    m_Customers = move(customers);
}

void VacationPark::setBookings(vector<unique_ptr<Booking>> bookings){
    m_Bookings = move(bookings);
}
