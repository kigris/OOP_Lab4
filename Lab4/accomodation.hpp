//
//  accomodation.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef accomodation_hpp
#define accomodation_hpp

#include <stdio.h>
#include <vector>
#include "luxuryLevel.hpp"
using  std::vector;

class Accomodation{
public:
    Accomodation(int id, int size, int numberPeople, bool bathroomWithBath, LuxuryLevel* luxuryLevel);
    ~Accomodation();
    inline const int getId() const {return m_ID;}
    bool setID(int id);
    inline const int getNumberPeople() const {return m_NumberPeople;}
    void setNumberPeople(int numberPeople);
    inline const int getSize() const {return m_Size;}
    void setSize(int size);
    inline const bool getBathroomWithBath() const {return m_BathroomWithBath;}
    void setBathroomWithBath(bool bathroomWithBath);
    inline const LuxuryLevel* getLuxuryLevel() const {return m_LuxuryLevel;}
    void setLuxuryLevel(LuxuryLevel* luxuryLevel);
private:
    static vector<int> g_IDs;
    int m_ID;
    int m_NumberPeople;
    int m_Size;
    bool m_BathroomWithBath;
    LuxuryLevel* m_LuxuryLevel;
};
#endif /* accomodation_hpp */
