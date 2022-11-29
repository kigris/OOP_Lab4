//
//  luxuryLevel.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#include "luxuryLevel.hpp"

LuxuryLevel::LuxuryLevel(bool hasBBQ, bool hasSurroundSystem, bool hasBreakfastService, bool hasCleaningService, string accomodationKind){
    setBBQ(hasBBQ);
    setSurroundSystem(hasSurroundSystem);
    setBreakfastService(hasBreakfastService);
    setCleaningService(hasCleaningService);
    setAccomodationKind(accomodationKind);
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
