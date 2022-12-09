//
//  hotelRoom.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 08/12/2022.
//

#ifndef hotelRoom_hpp
#define hotelRoom_hpp

#include <stdio.h>
#include <string>
#include "accomodation.hpp"
using namespace std;

class HotelRoom : public Accomodation {
public:
    // Constructor
    HotelRoom(int id, int capacityOfPeople, int size, bool bathroomWithBath, LuxuryLevel* luxuryLevel, int floor, string location, int numberOfBeds, bool childrenBed);
    
    // Getters
    inline const int getFloor() const {return m_Floor;}
    inline string getLocation() const {return m_Location;}
    inline int getNumberOfBeds() const {return m_NumberOfBeds;}
    inline bool getChildrenBed() const {return m_ChildrenBed;}
    
    // Setters
    void setFloor(int floor);
    void setLocation(string location);
    void setNumberOfBeds(int numberOfBeds);
    void setChildrenBed(bool childrenBed);
    
    // Overriden function
    void toString() override;
private:
    int m_Floor;
    string m_Location;
    int m_NumberOfBeds;
    bool m_ChildrenBed;
};
#endif /* hotelRoom_hpp */
