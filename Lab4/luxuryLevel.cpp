//
//  luxuryLevel.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#include "luxuryLevel.hpp"

LuxuryLevel::LuxuryLevel(bool hasBBQ, bool hasSurroundSystem, bool hasBreakfastService, bool hasCleaningService, string accomodationKind){
#ifdef DEBUG
    std::cout << "Luxury constructor called" << std::endl;
#endif
    setBBQ(hasBBQ);
    setSurroundSystem(hasSurroundSystem);
    setBreakfastService(hasBreakfastService);
    setCleaningService(hasCleaningService);
    setAccomodationKind(accomodationKind);
}

LuxuryLevel::~LuxuryLevel(){
#ifdef DEBUG
    std::cout << "Luxury destructor called" << std::endl;
#endif
}

void LuxuryLevel::setBBQ(bool has){
    m_BBQ = has;
}

void LuxuryLevel::setSurroundSystem(bool has){
    m_SurroundSystem = has;
}

void LuxuryLevel::setBreakfastService(bool has){
    m_BreakfastService = has;
}

void LuxuryLevel::setCleaningService(bool has){
    m_CleaningService = has;
}

void LuxuryLevel::setAccomodationKind(string accomodationKind){
    m_AccomodationKind = accomodationKind;
}

const string LuxuryLevel::toString() const{
    string result = "Luxury level: ";
    if (m_BBQ) {
        result += "BBQ, ";
    }
    if (m_SurroundSystem) {
        result += "Surround system, ";
    }
    if (m_BreakfastService) {
        result += "Breakfast service, ";
    }
    if (m_CleaningService) {
        result += "Cleaning service, ";
    }
    result += "Accomodation kind: " + m_AccomodationKind+"\n";
    return result;
}
