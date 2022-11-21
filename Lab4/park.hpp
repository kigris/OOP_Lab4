//
//  park.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef park_hpp
#define park_hpp

#include <stdio.h>
#include <string>
#include "service.hpp"
#include "accomodation.hpp"
#include <vector>
using std::string;
using std::vector;

class Park{
public:
    inline string getName() {return name;}
    void setName();
    inline string getAddress() {return address;}
    void setAddress();
    inline vector<Service> getServices() {return services;}
    void setServices();
    inline vector<Accomodation> getAcccomodations() {return accomodations;}
    void setAcccomodations();
private:
    string name;
    string address;
    vector<Service> services;
    vector<Accomodation> accomodations;
};
#endif /* park_hpp */
