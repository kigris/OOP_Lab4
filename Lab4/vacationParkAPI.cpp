//
//  customerAPI.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 29/11/2022.
//

#include "vacationParkAPI.hpp"

namespace customerAPI{
/// customerAPI namespace begin
///
///
bool createCustomer(VacationPark& vp, string name, string address, string mail){
    // We create the costumer
    unique_ptr<Customer> customer = make_unique<Customer>(name, address, mail);
    
    // Add the Costumer object to the list of costumers in vp
    try {
        vp.getCustomers().emplace_back(move(customer));
    } catch(exception){
        return false;
    }
    return true;
}


bool findCustomer(vector<unique_ptr<Customer>>& customers, string customerName){
    for(auto const& c : customers)
        if(convToLower(c->getName()) == convToLower(customerName))
            return true;
    return false;
}

bool findCustomer(vector<unique_ptr<Customer>>& customers, string customerName, Customer*& customer){
    for(auto const& c : customers)
        if(convToLower(c->getName()) == convToLower(customerName)){
            customer = c.get();
            return true;
        }
    
    return false;
}


bool updateCustomer(Customer*& customer, string name, string address, string mail){
    try {
        customer->setName(name);
        customer->setAddress(address);
        customer->setMail(mail);
    } catch(exception) {
        return false;
    }
    return true;
}
/// customerAPI namespace end
///
///
}



namespace ownerAPI{
/// ownerAPI namespace begin
///
///
bool findAccomodation(vector<unique_ptr<Park>>& parks, int id){
    // Look over all the parks
    for(auto const& p : parks)
        // Look over all the accomodations of a park
        for(auto const& a : p->getAcccomodations())
            if(a->getId() == id)
                return true;
    return false;
}

bool findPark(vector<unique_ptr<Park>>& parks, string parkName){
    for(auto const& p : parks)
        if(convToLower(p->getName()) == convToLower(parkName))
            return true;
    return false;
}

Park* getPark(VacationPark& vp, int index){
    return vp.getParks().at(index).get();
}

bool createPark(VacationPark& vp, string name, string address){
    // We create the costumer
    unique_ptr<Park> park = make_unique<Park>(name, address);
    
    // Add the Costumer object to the list of costumers in vp
    try {
        vp.getParks().emplace_back(move(park));
    } catch(exception){
        return false;
    }
    return true;
}

bool updateParkFeature(Park* park, string input, PARK_EDIT_OPT opt){
    switch (opt) {
        case PARK_EDIT_OPT::NAME:{
            return park->setName(input);
            break;
        }
        case PARK_EDIT_OPT::ADDRESS:
            park->setAddress(input);
            break;
        default:
            break;
    }
    
    return true;
}

bool updateParkMultipleFeatures(Park* park, bool input[]){
    Service* service = new Service{input[0],input[1],input[2],input[3],input[4],input[5]};
    park->setService(service);
    return true;
}

bool deletePark(int index, VacationPark& vp){
    vp.getParks().erase(vp.getParks().begin()+index);
    return true;
}
/// ownerAPI namespace end
///
///
}
