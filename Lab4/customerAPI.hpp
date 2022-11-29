//
//  customerAPI.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 29/11/2022.
//

#ifndef customerAPI_hpp
#define customerAPI_hpp

#include "customer.hpp"
#include <vector>
#include <string>
using std::vector;
using std::string;

bool findCustomer(vector<Customer*> customers, string customerName);
bool findCustomer(vector<Customer*> customers, string customerName, Customer*& customer);
#endif /* customerAPI_hpp */
