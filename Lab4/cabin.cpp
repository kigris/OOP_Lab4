//
//  cabin.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 08/12/2022.
//

#include "cabin.hpp"
// Constructor
Cabin::Cabin(int id, int size, int numberPeople, bool bathroomWithBath, LuxuryLevel* luxuryLevel, int bedrooms)
    : Accomodation(id, size, numberPeople, bathroomWithBath, luxuryLevel),
      m_Bedrooms(bedrooms) {
#ifdef DEBUG
    std::cout<<"DEBUG: Constructor - Cabin"<<std::endl;
#endif
      }

// Destructor
Cabin::~Cabin() {
#ifdef DEBUG
    std::cout<<"DEBUG: Destructor - Cabin"<<std::endl;
#endif
}

// Setter
void Cabin::setBedrooms(int bedrooms) {
  m_Bedrooms = bedrooms;
}

const string Cabin::toString() const {
    ostringstream os;
    string bathroomWithBathString = getBathroomWithBath() ? "Yes" : "No";
    // Print headers
    os << "| " << std::right << std::setw(3) << "ID"<<" | " << std::setw(4) << "Size"
    <<" | " << std::setw(16) << "Number of people"<<" | "  << std::setw(18) << "Bathroom with bath"
    <<" | "<< std::setw(8) << "Bedrooms"<<" |"<<std::endl;
    // Print data
    os << "| " << std::right << std::setw(3) << getId() <<" | " << std::setw(4) << getSize()
    <<" | " << std::setw(16) << getNumberPeople() <<" | "  <<std::setw(18) << bathroomWithBathString
    <<" | " << std::setw(8) << m_Bedrooms << " |"<<std::endl;
    // Print luxury level
    os<<getLuxuryLevel()->toString();
    return os.str();
}
