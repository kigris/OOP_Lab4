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
    Park(string name);
    Park(string name, string address, vector<Service*> services, vector<Accomodation*> accomodations);
    ~Park();
    inline string getName() {return m_Name;}
    bool setName(string name);
    inline string getAddress() {return m_Address;}
    void setAddress(string address);
    inline vector<Service*> getServices() {return m_Services;}
    void setServices(vector<Service*> services);
    inline vector<Accomodation*> getAcccomodations() {return m_Accomodations;}
    void setAcccomodations(vector<Accomodation*> accomodations);
private:
    static vector<string> g_Names;
    string m_Name;
    string m_Address;
    vector<Service*> m_Services;
    vector<Accomodation*> m_Accomodations;
};
#endif /* park_hpp */
