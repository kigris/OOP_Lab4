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
    ParkCompany(string name, string address);
    ParkCompany(string name, string address, vector<Park*> parks, vector<Customer*> customers, vector<Booking*> bookings);
    ~ParkCompany();
    inline string getName() {return m_Name;}
    bool setName(string name);
    inline string getAddress() {return m_Address;}
    void setAddress(string address);
    inline vector<Park*> getParks() {return m_Parks;}
    void setParks(vector<Park*> parks);
    inline vector<Customer*> getCustomers() {return m_Customers;}
    void setCustomers(vector<Customer*> customers);
    inline vector<Booking*> getBookings() {return m_Bookings;}
    void setBookings(vector<Booking*> bookings);
private:
    static vector<string> g_Names;
    string m_Name;
    string m_Address;
    vector<Park*> m_Parks;
    vector<Customer*> m_Customers;
    vector<Booking*> m_Bookings;
};
#endif /* parkCompany_hpp */
