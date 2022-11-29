//
//  parkCompany.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#include "parkCompany.hpp"

vector<string> ParkCompany::g_Names = {};

ParkCompany::ParkCompany(string name, string address){
    m_Parks = {};
    m_Customers = {};
    m_Bookings = {};
}

ParkCompany::ParkCompany(string name, string address, vector<Park*> parks, vector<Customer*> customers, vector<Booking*> bookings){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
    setParks(parks);
    setCustomers(customers);
    setBookings(bookings);
}

ParkCompany::~ParkCompany(){
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
    // Delete parks, customers and bookings
    for(auto p : m_Parks)
        delete p;
    for(auto c : m_Customers)
        delete c;
    for(auto b : m_Bookings)
        delete b;
}

bool ParkCompany::setName(string name){
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

void ParkCompany::setAddress(string address){
    m_Address = address;
}

void ParkCompany::setParks(vector<Park*> parks){
    m_Parks = parks;
}

void ParkCompany::setCustomers(vector<Customer*> customers){
    m_Customers = customers;
}

void ParkCompany::setBookings(vector<Booking*> bookings){
    m_Bookings = bookings;
}
