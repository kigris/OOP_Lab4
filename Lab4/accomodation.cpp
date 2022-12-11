//
//  accomodation.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#include "accomodation.hpp"

// Initialization of the static global IDs
vector<int> Accomodation::g_IDs = {};

Accomodation::Accomodation(int id, int size, int numberPeople, bool bathroomWithBath, LuxuryLevel* luxuryLevel){
    if(!setID(id)){
        throw std::invalid_argument("Duplicate ID");
    }
    setNumberPeople(numberPeople);
    setSize(size);
    setBathroomWithBath(bathroomWithBath);
    setLuxuryLevel(luxuryLevel);
}

Accomodation::~Accomodation(){
#ifdef DEBUG
    std::cout<<"DEBUG: Accomodation with ID "<< m_ID << ", destructor called, before cleaning, g_IDS size: " << g_IDs.size() <<std::endl;
#endif
    // We remove the ID from the list of IDs used
    g_IDs.erase(remove(g_IDs.begin(), g_IDs.end(), m_ID), g_IDs.end());
    // Delete the luxuryLevel memory
    delete m_LuxuryLevel;
#ifdef DEBUG
    std::cout<<"DEBUG: Accomodation with ID "<< m_ID << ", destructor called, after cleaning, g_IDS size: " << g_IDs.size() <<std::endl;
#endif
}

bool Accomodation::setID(int id){
    // Check that the id is not taken
    for(int i : g_IDs)
        if(i==id)
            return false;
    // We remove the current one
    g_IDs.erase(remove(g_IDs.begin(), g_IDs.end(), m_ID), g_IDs.end());
    // If the id given is not taken
    m_ID = id;
    // We add the id given to the IDs taken
    g_IDs.push_back(id);
    return true;
}

void Accomodation::setNumberPeople(int numberPeople){
    m_NumberPeople = numberPeople;
}

void Accomodation::setSize(int size){
    m_Size = size;
}

void Accomodation::setBathroomWithBath(bool bathroomWithBath){
    m_BathroomWithBath = bathroomWithBath;
}

void Accomodation::setLuxuryLevel(LuxuryLevel* luxuryLevel){
    // If there is one existing luxuryLevel, free the memory in the heap
    if(m_LuxuryLevel!=nullptr)
        delete m_LuxuryLevel;
    // Assign the new pointer with the new memory
    m_LuxuryLevel = luxuryLevel;
}
