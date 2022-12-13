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
#include <iostream>
#include "luxuryLevel.hpp"
using  std::vector;

class Accomodation{
public:
    Accomodation(int id, int size, int numberPeople, bool bathroomWithBath, LuxuryLevel* luxuryLevel);
    // Virtual destructor, important for ensuring proper cleaning of derived clases
    virtual ~Accomodation();
    
    // Getters
    inline const int getId() const {return m_ID;}
    inline const int getNumberPeople() const {return m_NumberPeople;}
    inline const int getSize() const {return m_Size;}
    inline const bool getBathroomWithBath() const {return m_BathroomWithBath;}
    inline const LuxuryLevel* getLuxuryLevel() const {return m_LuxuryLevel;}
    inline const bool isReserved() const {return m_inUse;}
    
    // Setters
    bool setID(int id);
    void setNumberPeople(int numberPeople);
    void setSize(int size);
    void setBathroomWithBath(bool bathroomWithBath);
    void setLuxuryLevel(LuxuryLevel* luxuryLevel);
    inline void reserve(){m_inUse=true;}
    inline void release(){m_inUse=false;}
    inline static vector<int>& getGlobalIDs(){return g_IDs;}
    inline static void setGlobalIDs(vector<int>& ids){g_IDs=ids;}
    
    // Other functions
    virtual void toString()=0; // Pure virtual function
private:
    static vector<int> g_IDs;
    bool m_inUse{false};
    int m_ID;
    int m_NumberPeople;
    int m_Size;
    bool m_BathroomWithBath;
    LuxuryLevel* m_LuxuryLevel{nullptr};
};
#endif /* accomodation_hpp */
