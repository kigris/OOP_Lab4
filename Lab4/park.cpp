//
//  park.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#include "park.hpp"
#include <string>
#include <vector>
#include "service.hpp"
#include "accomodation.hpp"
using std::string;
using std::vector;

vector<string> Park::g_Names={};

Park::Park(string name){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
};

Park::Park(string name, string address, vector<Service*> services, vector<Accomodation*> accomodations){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
    setServices(services);
    setAcccomodations(accomodations);
}

Park::~Park(){
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
    // Delete services and accomodations
    for(auto s : m_Services)
        delete s;
    for(auto a : m_Accomodations)
        delete a;
}

bool Park::setName(string name) {
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

void Park::setAddress(string address){
    m_Address = address;
}

void Park::setServices(vector<Service*> services){
    m_Services = services;
}

void Park::setAcccomodations(vector<Accomodation*> accomodations){
    m_Accomodations = accomodations;
}
