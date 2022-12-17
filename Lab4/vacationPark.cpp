//
//  vacationPark.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#include "vacationPark.hpp"

vector<string> VacationPark::g_Names = {};

VacationPark::VacationPark(string name, string address){
#ifdef DEBUG
    std::cout<<"DEBUG: Creating vacation park with name: "<<name<<", address: "<<
    address<<", g_Names size before: "<<g_Names.size()<<std::endl;
#endif
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
#ifdef DEBUG
    std::cout<<"DEBUG: Successfully created vacation park with name: "<<name<<", address: "<<
    address<<", g_Names size after: "<<g_Names.size()<<std::endl;
#endif
}

VacationPark::VacationPark(string name, string address, vector<unique_ptr<Park>> parks, vector<unique_ptr<Customer>> customers, vector<unique_ptr<Booking>> bookings){
#ifdef DEBUG
    std::cout<<"DEBUG: Creating vacation park with name: "<<name<<", address: "<<
    address<<", g_Names size before: "<<g_Names.size()<<std::endl;
#endif
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
    m_Parks = move(parks);
    m_Customers = move(customers);
    m_Bookings = move(bookings);
#ifdef DEBUG
    std::cout<<"DEBUG: Successfully created vacation park with name: "<<name<<", address: "<<
    address<<", g_Names size after: "<<g_Names.size()<<std::endl;
#endif
}

VacationPark::~VacationPark(){
#ifdef DEBUG
    std::cout<<"DEBUG: Deleting vacation park with name: "<<m_Name<<", address: "<<m_Address<<
    ", g_Names size before: "<<g_Names.size()<<std::endl;
#endif
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
#ifdef DEBUG
    std::cout<<"DEBUG: Successfully deleted vacation park with name: "<<m_Name<<", address: "<<m_Address<<
    ", g_Names size after: "<<g_Names.size()<<std::endl;
#endif
}

bool VacationPark::setName(string name){
    // Check that the name is not taken
    for(string n : g_Names)
        if(n==name)
            return false;
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
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
