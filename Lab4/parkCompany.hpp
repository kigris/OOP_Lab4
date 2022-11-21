//
//  parkCompany.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#ifndef parkCompany_hpp
#define parkCompany_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "customer.hpp"
#include "park.hpp"
#include "booking.hpp"
using std::string;
using std::vector;

class ParkCompany{
public:
    inline string getName() {return name;}
    void setName();
    inline string getAddress() {return address;}
    void setAddress();
    inline vector<Park> getParks() {return parks;}
    void setParks();
    inline vector<Customer> getCustomer() {return customers;}
    void setCustomer();
    inline vector<Booking> getBookings() {return bookings;}
    void setBookings();
private:
    string name;
    string address;
    vector<Park> parks;
    vector<Customer> customers;
    vector<Booking> bookings;
};
#endif /* parkCompany_hpp */
