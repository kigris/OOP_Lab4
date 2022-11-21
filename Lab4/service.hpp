//
//  service.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef service_hpp
#define service_hpp

#include <stdio.h>
#include <string>
using std::string;
class Service{
public:
    inline bool getSubtropicSwimmingPool() {return subtropicSwimmingPool;}
    void setSubtropicSwimmingPool();
    inline bool getSportsInfrastructure() {return sportsInfrastructure;}
    void setSportsInfrastructure();
    bool bowlingAlley;
    inline bool getBowlingAlley() {return bowlingAlley;}
    void setBowlingAlley();
    inline bool getBicycleRent() {return bicycleRent;}
    void setBicycleRent();
    inline bool getChildrenParadise() {return childrenParadise;}
    void setChildrenParadise();
    inline bool getWaterBikes() {return waterBikes;}
    void setWaterBikes();
private:
    bool subtropicSwimmingPool;
    bool sportsInfrastructure;
    bool bicycleRent;
    bool childrenParadise;
    bool waterBikes;
};
#endif /* service_hpp */
