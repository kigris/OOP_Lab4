//
//  cabin.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 08/12/2022.
//

#ifndef cabin_hpp
#define cabin_hpp

#include <stdio.h>
#include "accomodation.hpp"
#include <stdexcept>
using namespace std;
// Cabin class
class Cabin : public Accomodation {
public:
    // Constructor
    Cabin(int id, int size, int numberPeople, bool bathroomWithBath, LuxuryLevel* luxuryLevel, int bedrooms);
    // Destructor
    ~Cabin();
    
    // Getter
    inline int getBedrooms() const {return m_Bedrooms;}
    
    // Setter
    void setBedrooms(int bedrooms);
    
    // Overriden function
    const string toString() const override;
private:
    int m_Bedrooms;
};
#endif /* cabin_hpp */
