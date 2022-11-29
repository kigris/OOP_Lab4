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
    Service(bool hasSubtropicSwimmingPool, bool hasSportsInfrastructure, bool hasBowlingAlley, bool hasBicycleRent, bool hasChildrenParadise, bool hasWaterBikes);
    inline bool getSubtropicSwimmingPool() {return m_SubtropicSwimmingPool;}
    void setSubtropicSwimmingPool(bool has);
    inline bool getSportsInfrastructure() {return m_SportsInfrastructure;}
    void setSportsInfrastructure(bool has);
    inline bool getBowlingAlley() {return m_BowlingAlley;}
    void setBowlingAlley(bool has);
    inline bool getBicycleRent() {return m_BicycleRent;}
    void setBicycleRent(bool has);
    inline bool getChildrenParadise() {return m_ChildrenParadise;}
    void setChildrenParadise(bool has);
    inline bool getWaterBikes() {return m_WaterBikes;}
    void setWaterBikes(bool has);
private:
    bool m_SubtropicSwimmingPool;
    bool m_SportsInfrastructure;
    bool m_BowlingAlley;
    bool m_BicycleRent;
    bool m_ChildrenParadise;
    bool m_WaterBikes;
};
#endif /* service_hpp */
