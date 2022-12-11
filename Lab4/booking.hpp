//
//  booking.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef booking_hpp
#define booking_hpp

#include <stdio.h>
#include <string>
#include "customer.hpp"
#include "accomodation.hpp"
#include <vector>
using std::string;
using std::vector;

class Booking{
public:
    // Constructors, destructors
    Booking(string id, Customer* customer, bool activityPass, bool bicycleRent, bool swimmingPass);
    Booking(string id, Customer* customer, vector<Accomodation*> accomodations, bool activityPass, bool bicycleRent, bool swimmingPass);
    ~Booking();
    
    inline string getId(){return m_ID;}
    bool setID(string id);
    inline Customer* getCustomer() {return m_Customer;}
    void setCustomer(Customer* customer);
    inline vector<Accomodation*>& getAccomodations() {return m_Accomodations;}
    void setAccomodations(vector<Accomodation*> accomodations);
    inline bool getActivityPass() {return m_ActivityPass;}
    void setActivityPass(bool activityPass);
    inline bool getSportsPass() {return m_SportsPass;}
    void setSportsPass(bool sportsPass);
    inline bool getBicycleRentPass() {return m_BicyleRentPass;}
    void setBicycleRentPass(bool bicycleRent);
    inline bool getSwimmingPass() {return m_SwimmingPass;}
    void setSwimmingPass(bool swimmingPass);
private:
    static vector<string> g_IDs;
    string m_ID;
    Customer* m_Customer{nullptr};
    vector<Accomodation*> m_Accomodations;
    bool m_ActivityPass;
    bool m_SportsPass;
    bool m_BicyleRentPass;
    bool m_SwimmingPass;
};

#endif /* booking_hpp */
