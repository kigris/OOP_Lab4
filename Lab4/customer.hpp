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
using std::string;
class Customer{
public:
    inline string getName() {return name;}
    void setName();
    inline string getAddress() {return address;}
    void setAddress();
    inline string getMail() {return mail;}
    void setMail();
private:
    string name;
    string address;
    string mail;
};
#endif /* customer_hpp */
