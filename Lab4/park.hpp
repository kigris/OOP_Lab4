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
#include <stdexcept>
#include "accomodation.hpp"
#include <vector>
#include "hotelRoom.hpp"
#include <algorithm>
using std::string;
using std::vector;

class Park{
public:
    Park()=default;
    Park(string name, string address, Service* service);
    Park(string name, string address, Service* services, vector<Accomodation*> accomodations);
    ~Park();
    inline string& getName() {return m_Name;}
    bool setName(string name);
    inline string getAddress() {return m_Address;}
    void setAddress(string address);
    inline Service* getService() {return m_Service;}
    void setService(Service* service);
    inline vector<Accomodation*>& getAccomodations() {return m_Accomodations;}
    void setAcccomodations(vector<Accomodation*> accomodations);
    inline static vector<string>& getGlobalNames(){return g_Names;}
    inline static void setGlobalNames(vector<string>& names){g_Names=names;}
    inline bool isReferenced(){return m_References>0;}
    inline int getReferences(){return m_References;}
    inline void setReferences(int references){m_References=references;}
    inline void incrementReferences(){m_References++;}
    inline void decrementReferences(){m_References--;}
private:
    static vector<string> g_Names;
    int m_References {0};
    string m_Name;
    string m_Address;
    Service* m_Service {nullptr};
    vector<Accomodation*> m_Accomodations{};
};
#endif /* park_hpp */
