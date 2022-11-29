//
//  customer.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef customer_hpp
#define customer_hpp

#include <stdio.h>
#include <string>
#include <vector>
using std::vector;

using std::string;
class Customer{
public:
    Customer(string name, string address, string mail);
    ~Customer();
    inline string getName() {return m_Name;}
    bool setName(string name);
    inline string getAddress() {return m_Address;}
    void setAddress(string address);
    inline string getMail() {return m_Mail;}
    void setMail(string mail);
private:
    static vector<string> g_Names;
    string m_Name;
    string m_Address;
    string m_Mail;
};
#endif /* customer_hpp */
