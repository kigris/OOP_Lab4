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
    inline int getId();
    void setId(int n_id);
    inline Customer getCustomer() {return customer;}
    void setCustomer();
    inline vector<Accomodation> getAccomodations() {return accomodations;}
    void setAccomodations();
    inline bool getActivityPass() {return activityPass;}
    void setActivityPass();
    inline bool getBicycleRent() {return bicyleRent;}
    void setBicycleRent();
    inline bool getSwimmingPass() {return swimmingPass;}
    void setSwimmingPass();
private:
    int id;
    Customer customer;
    vector<Accomodation> accomodations;
    bool activityPass;
    bool bicyleRent;
    bool swimmingPass;
};

#endif /* booking_hpp */
