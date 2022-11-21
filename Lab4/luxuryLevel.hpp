//
//  luxuryLevel.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#ifndef luxuryLevel_hpp
#define luxuryLevel_hpp

#include <stdio.h>
#include <string>
using std::string;
class LuxuryLevel {
public:
    inline bool getBBQ() {return BBQ;}
    void setBBQ();
    inline bool getSurroundSystem() {return surroundSystem;}
    void setSurroundSystem();
    inline bool getBreakfastService() {return breakfastService;}
    void setBreakfastService();
    inline bool getCleaningService() {return cleaningService;}
    void setCleaningService();
    inline string getAccomodationKind() {return accomodationKind;}
    void setAccomodationKind();
private:
    bool BBQ;
    bool surroundSystem;
    bool breakfastService;
    bool cleaningService;
    string accomodationKind;
};
#endif /* luxuryLevel_hpp */
