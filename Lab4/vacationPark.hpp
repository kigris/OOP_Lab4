//
//  vacationPark.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 21/11/2022.
//

#ifndef vacationPark_hpp
#define vacationPark_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include "customer.hpp"
#include <stdexcept>
#include "park.hpp"
#include "booking.hpp"
using namespace std;

class VacationPark{
public:
    VacationPark(){};
    VacationPark(string name, string address, int VAT);
    VacationPark(string name, string address, int VAT, vector<unique_ptr<Park>> parks, vector<unique_ptr<Customer>> customers, vector<unique_ptr<Booking>> bookings);
    ~VacationPark();
    
    // Setters
    bool setName(string name);
    void setAddress(string address);
    void setVAT(int VAT);
    void setParks(vector<unique_ptr<Park>> parks);
    void setCustomers(vector<unique_ptr<Customer>> customers);
    void setBookings(vector<unique_ptr<Booking>> bookings);
    
    // Getters
    inline int getVAT() {return m_VAT;}
    inline string getName() {return m_Name;}
    inline string getAddress() {return m_Address;}
    inline vector<unique_ptr<Park>>& getParks() {return m_Parks;}
    inline vector<unique_ptr<Customer>>& getCustomers() {return m_Customers;}
    inline vector<unique_ptr<Booking>>& getBookings() {return m_Bookings;}
private:
    static vector<string> g_Names;
    string m_Name;
    string m_Address;
    int m_VAT;
    vector<unique_ptr<Park>> m_Parks;
    vector<unique_ptr<Customer>> m_Customers;
    vector<unique_ptr<Booking>> m_Bookings;
};
#endif /* vacationPark_hpp */
