//
//  accomodation.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef accomodation_hpp
#define accomodation_hpp

#include <stdio.h>
#include "luxuryLevel.hpp"
class Accomodation{
public:
    inline int getId() {return id;}
    void setId();
    inline int getNumberPeople() {return numberPeople;}
    void setNumberPeople();
    inline int getSize() {return size;}
    void setSize();
    inline bool getBathroomWithBath() {return bathroomWithBath;}
    void setBathroomWithBath();
    inline LuxuryLevel getLuxuryLevel() {return luxuryLevel;}
    void setLuxuryLevel();
private:
    int id;
    int numberPeople;
    int size;
    bool bathroomWithBath;
    LuxuryLevel luxuryLevel;
};
#endif /* accomodation_hpp */
