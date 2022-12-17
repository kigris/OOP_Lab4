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
m_ChildrenBed(childrenBed) {
#ifdef DEBUG
    std::cout<<"DEBUG: Constructor - HotelRoom"<<std::endl;
#endif
}

// Destructor
HotelRoom::~HotelRoom() {
#ifdef DEBUG
    std::cout<<"DEBUG: Destructor - HotelRoom"<<std::endl;
#endif
}

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

const string HotelRoom::toString() const {
    ostringstream os;
    // Bathroom with bath
    string bathroomWithBathString = getBathroomWithBath() ? "Yes" : "No";
    // Children bed
    string childrenBedString = m_ChildrenBed ? "Yes" : "No";
    // Print headers
    os << "| " << std::right << std::setw(3) << "ID"<<" | " << std::setw(4) << "Size"
    <<" | " << std::setw(16) << "Number of people"<<" | "  << std::setw(18) << "Bathroom with bath"
    <<" | "<< std::setw(5) << "Floor"<<" | " << std::setw(14) << "Number of beds" <<" | "
    << std::setw(12) << "Children bed" << " | "<< std::setw(20) << "Location"<< " |"<<std::endl;
    // Print data to be in the middle of each column and replace "|"" with " "
    os << "| " << std::right << std::setw(3) << getId() <<" | " << std::setw(4) << getSize()
    <<" | " << std::setw(16) << getNumberPeople() <<" | "  <<std::setw(18) << bathroomWithBathString
    <<" | " << std::setw(5) << m_Floor <<" | " << std::setw(14) << m_NumberOfBeds
    <<" | " << std::setw(12) << childrenBedString<<" | "  << std::setw(20) << m_Location << " |"<<std::endl; 
    // Print luxury level
    os<<getLuxuryLevel()->toString();
    return os.str();
}
