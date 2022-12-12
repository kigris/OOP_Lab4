//
//  customer.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#include "customer.hpp"

vector<string> Customer::g_Names={};

Customer::Customer(string name, string address, string mail){
    if(!setName(name)){
        throw std::invalid_argument("Duplicate ID");
    }
    setAddress(address);
    setMail(mail);
}

Customer::~Customer(){
#ifdef DEBUG
    std::cout<< "DEBUG: Destructor - Customer with name " << m_Name << ", before cleaning, g_Names size: " << g_Names.size() <<std::endl;
#endif
    // We remove the name from the list of names used
    g_Names.erase(remove(g_Names.begin(), g_Names.end(), m_Name), g_Names.end());
#ifdef DEBUG
    std::cout<< "DEBUG: Destructor -  Customer with name " << m_Name << ", after cleaning, g_Names size: " << g_Names.size() <<std::endl;
#endif
}

bool Customer::setName(string name){
    // Check that the id is not taken
    for(string n : g_Names)
        if(n==name)
            return false;
    // If the id given is not found
    m_Name = name;
    // We add the id given to the IDs taken
    g_Names.push_back(name);
    return true;
}

void Customer::setAddress(string address){
    m_Address = address;
}

void Customer::setMail(string mail){
    m_Mail = mail;
}
