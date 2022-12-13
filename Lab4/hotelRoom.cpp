//
//  hotelRoom.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 08/12/2022.
//

#include "hotelRoom.hpp"
// Constructor
HotelRoom::HotelRoom(int id, int size, int numberPeople, bool bathroomWithBath, LuxuryLevel* luxuryLevel, int floor, string location, int numberOfBeds, bool childrenBed)
    : Accomodation(id, size, numberPeople, bathroomWithBath, luxuryLevel),
      m_Floor(floor),
      m_Location(location),
      m_NumberOfBeds(numberOfBeds),
      m_ChildrenBed(childrenBed) {}

// Setters
void HotelRoom::setFloor(int floor) {
  m_Floor = floor;
}

void HotelRoom::setLocation(std::string location) {
  m_Location = location;
}

void HotelRoom::setNumberOfBeds(int numberOfBeds) {
  m_NumberOfBeds = numberOfBeds;
}

void HotelRoom::setChildrenBed(bool childrenBed) {
  m_ChildrenBed = childrenBed;
}

void HotelRoom::toString() {
    cout<<"Hello from HotelRoom"<<endl;
}
