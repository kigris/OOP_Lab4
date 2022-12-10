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

Park::Park(string name, string address, Service* service){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
    setService(service);
};

Park::Park(string name, string address, Service* service, vector<Accomodation*> accomodations){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate name");
    }
    setAddress(address);
    setService(service);
    setAcccomodations(accomodations);
}

Park::~Park(){
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
    // Delete accomodations
    for(auto a : m_Accomodations)
        delete a;
    // Free up the service
    delete m_Service;
}

bool Park::setName(string name) {
    // Check we are not trying to assing the same name
    if(name == m_Name)
        return false;
    // Check that the name is not taken
    for(string n : g_Names)
        if(n==name)
            return false;
    // First we erase the current one
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
    // If the name given is not found
    m_Name = name;
    // We add the name given to the names taken
    g_Names.push_back(name);
    return true;
}

void Park::setAddress(string address){
    m_Address = address;
}

void Park::setService(Service* service){
    // If we have a service set already
    if(m_Service!=nullptr)
        // Free the memory of that service
        delete m_Service;
    m_Service = service; // Assign the new service
}

void Park::setAcccomodations(vector<Accomodation*> accomodations){
    // If the accomodations are not empty
    if(!accomodations.empty())
        // Go through all the elements of accomodations
        for(auto acc : accomodations)
            delete acc; // Delete the memory
    accomodations.clear(); // Clear the vector
    m_Accomodations = accomodations;
}
