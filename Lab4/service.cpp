//
//  service.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#include "service.hpp"

Service::Service(bool hasSubtropicSwimmingPool, bool hasSportsInfrastructure, bool hasBowlingAlley, bool hasBicycleRent, bool hasChildrenParadise, bool hasWaterBikes){
#ifdef DEBUG
    std::cout << "Service constructor called" << std::endl;
#endif
    setSubtropicSwimmingPool(hasSubtropicSwimmingPool);
    setSportsInfrastructure(hasSportsInfrastructure);
    setBowlingAlley(hasBowlingAlley);
    setBicycleRent(hasBicycleRent);
    setChildrenParadise(hasChildrenParadise);
    setWaterBikes(hasWaterBikes);
}

Service::~Service(){
#ifdef DEBUG
    std::cout << "Service destructor called" << std::endl;
#endif
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
std::ostream& operator<<(std::ostream& out, const Service& service){
    string result = "Service: ";
    if (service.m_SubtropicSwimmingPool) {
        result += "Subtropic swimming pool, ";
    }
    if (service.m_SportsInfrastructure) {
        result += "Sports infrastructure, ";
    }
    if (service.m_BowlingAlley) {
        result += "Bowling alley, ";
    }
    if (service.m_BicycleRent) {
        result += "Bicycle rent, ";
    }
    if (service.m_ChildrenParadise) {
        result += "Children paradise, ";
    }
    if (service.m_WaterBikes) {
        result += "Water bikes";
    }
    return out << result;
}