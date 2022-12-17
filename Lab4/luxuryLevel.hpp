//
//  luxuryLevel.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#ifndef luxuryLevel_hpp
#define luxuryLevel_hpp

#ifdef DEBUG
#include <iostream>
#endif
#include <stdio.h>
#include <stdexcept>
#include <string>
using std::string;
class LuxuryLevel {
public:
    LuxuryLevel()=default;
    LuxuryLevel(bool hasBBQ, bool hasSurroundSystem, bool hasBreakfastService, bool hasCleaningService, string hasAccomodationKind);
    ~LuxuryLevel();
    inline bool getBBQ() const {return m_BBQ;}
    void setBBQ(bool has);
    inline bool getSurroundSystem() const {return m_SurroundSystem;}
    void setSurroundSystem(bool has);
    inline bool getBreakfastService() const {return m_BreakfastService;}
    void setBreakfastService(bool has);
    inline bool getCleaningService() const {return m_CleaningService;}
    void setCleaningService(bool has);
    inline string getAccomodationKind() const {return m_AccomodationKind;}
    void setAccomodationKind(string accomodationKind);
    const string toString() const;
private:
    bool m_BBQ;
    bool m_SurroundSystem;
    bool m_BreakfastService;
    bool m_CleaningService;
    string m_AccomodationKind;
};
#endif /* luxuryLevel_hpp */
