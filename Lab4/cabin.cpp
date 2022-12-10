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
      m_Bedrooms(bedrooms) {}

// Setter
void Cabin::setBedrooms(int bedrooms) {
  m_Bedrooms = bedrooms;
}

void Cabin::toString() {
    
}
