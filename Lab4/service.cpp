//
//  service.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#include "service.hpp"

Service::Service():
    m_SubtropicSwimmingPool(false),
    m_SportsInfrastructure(false),
    m_BowlingAlley(false),
    m_BicycleRent(false),
    m_ChildrenParadise(false),
    m_WaterBikes(false){}

Service::Service(bool hasSubtropicSwimmingPool, bool hasSportsInfrastructure, bool hasBowlingAlley, bool hasBicycleRent, bool hasChildrenParadise, bool hasWaterBikes){
    setSubtropicSwimmingPool(hasSubtropicSwimmingPool);
    setSportsInfrastructure(hasSportsInfrastructure);
    setBowlingAlley(hasBowlingAlley);
    setBicycleRent(hasBicycleRent);
    setChildrenParadise(hasChildrenParadise);
    setWaterBikes(hasWaterBikes);
}

void Service::setSubtropicSwimmingPool(bool has){
    m_SubtropicSwimmingPool = has;
}

void Service::setSportsInfrastructure(bool has){
    m_SportsInfrastructure = has;
}

void Service::setBowlingAlley(bool has){
    m_BowlingAlley = has;
}

void Service::setBicycleRent(bool has){
    m_BicycleRent = has;
}

void Service::setChildrenParadise(bool has){
    m_ChildrenParadise = has;
}

void Service::setWaterBikes(bool has){
    m_WaterBikes = has;
}
