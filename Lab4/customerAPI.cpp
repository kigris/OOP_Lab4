//
//  customerAPI.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 29/11/2022.
//

#include "customerAPI.hpp"

bool findCustomer(vector<Customer*> customers, string customerName){
    for(auto c:customers)
        if(c->getName()==customerName)
            return true;
        
    return false;
}

bool findCustomer(vector<Customer*> customers, string customerName, Customer*& costumer){
    for(auto c:customers)
        if(c->getName()==customerName){
            costumer = c;
            return true;
        }
    return false;
}
