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

Accomodation* getAccomodation(VacationPark& vp, int parkIndex, int accomodationIndex){
    return vp.getParks().at(parkIndex).get()->getAcccomodations().at(accomodationIndex);
}

bool createPark(VacationPark& vp, string name, string address, Service* service){
    // We create the costumer
    unique_ptr<Park> park = make_unique<Park>(name, address, service);
    
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

bool updateParkServices(Park* park, bool input[]){
    Service* service = new Service{input[0],input[1],input[2],input[3],input[4],input[5]};
    park->setService(service);
    return true;
}

bool deletePark(int index, VacationPark& vp){
    vector<unique_ptr<Park>>& parks = vp.getParks();
    parks.erase(parks.begin()+index);
    return true;
}

Service* createService(map<int,void*>* args){
    return new Service((static_cast<Value<bool>*>(args->at(1)))->value,
                       (static_cast<Value<bool>*>(args->at(2)))->value,
                       (static_cast<Value<bool>*>(args->at(3)))->value,
                       (static_cast<Value<bool>*>(args->at(4)))->value,
                       (static_cast<Value<bool>*>(args->at(5)))->value,
                       (static_cast<Value<bool>*>(args->at(6)))->value);
}

bool createAccomodation(vector<Accomodation*>& accomodations, map<int,void*>* args, ACC_TYPE type){
    if(type==ACC_TYPE::HOTELROOM){
        // Build the luxuryLevel object first
        LuxuryLevel* luxuryLevel = new LuxuryLevel((static_cast<Value<bool>*>(args->at(9)))->value,
                                                   (static_cast<Value<bool>*>(args->at(10)))->value,
                                                   (static_cast<Value<bool>*>(args->at(11)))->value,
                                                   (static_cast<Value<bool>*>(args->at(12)))->value,
                                                   (static_cast<Value<string>*>(args->at(13)))->value);
        Accomodation* hotelRoom = new HotelRoom((static_cast<Value<int>*>(args->at(1)))->value,
                                                (static_cast<Value<int>*>(args->at(2)))->value,
                                                (static_cast<Value<int>*>(args->at(3)))->value,
                                                (static_cast<Value<bool>*>(args->at(4)))->value,
                                                luxuryLevel,
                                                (static_cast<Value<int>*>(args->at(5)))->value,
                                                (static_cast<Value<string>*>(args->at(6)))->value,
                                                (static_cast<Value<int>*>(args->at(7)))->value,
                                                (static_cast<Value<bool>*>(args->at(8)))->value);
        accomodations.emplace_back(hotelRoom);
        return true;
    } else if(type==ACC_TYPE::CABIN){
        // Build the luxuryLevel object first
        LuxuryLevel* luxuryLevel = new LuxuryLevel((static_cast<Value<bool>*>(args->at(6)))->value,
                                                   (static_cast<Value<bool>*>(args->at(7)))->value,
                                                   (static_cast<Value<bool>*>(args->at(8)))->value,
                                                   (static_cast<Value<bool>*>(args->at(9)))->value,
                                                   (static_cast<Value<string>*>(args->at(10)))->value);
        Accomodation* cabin = new Cabin((static_cast<Value<int>*>(args->at(1)))->value,
                                        (static_cast<Value<int>*>(args->at(2)))->value,
                                        (static_cast<Value<int>*>(args->at(3)))->value,
                                        (static_cast<Value<bool>*>(args->at(4)))->value,
                                        luxuryLevel,
                                        (static_cast<Value<int>*>(args->at(5)))->value);
        accomodations.emplace_back(cabin);
        return true;
    }
    return false;
}

bool updateAccomodation(Accomodation* accomodation, map<int,void*>* args, ACC_TYPE type){
    if(type==ACC_TYPE::HOTELROOM){
        // Build the luxuryLevel object first
        LuxuryLevel* luxuryLevel = new LuxuryLevel((static_cast<Value<bool>*>(args->at(9)))->value,
                                                   (static_cast<Value<bool>*>(args->at(10)))->value,
                                                   (static_cast<Value<bool>*>(args->at(11)))->value,
                                                   (static_cast<Value<bool>*>(args->at(12)))->value,
                                                   (static_cast<Value<string>*>(args->at(13)))->value);
        // Update the hotelroom accomodation
        HotelRoom* hotelRoom = dynamic_cast<HotelRoom*>(accomodation);
        hotelRoom->setID((static_cast<Value<int>*>(args->at(1)))->value);
        hotelRoom->setNumberPeople((static_cast<Value<int>*>(args->at(2)))->value);
        hotelRoom->setSize((static_cast<Value<int>*>(args->at(3)))->value);
        hotelRoom->setBathroomWithBath((static_cast<Value<bool>*>(args->at(4)))->value);
        hotelRoom->setBathroomWithBath(luxuryLevel);
        hotelRoom->setFloor((static_cast<Value<int>*>(args->at(5)))->value);
        hotelRoom->setLocation((static_cast<Value<string>*>(args->at(6)))->value);
        hotelRoom->setNumberOfBeds((static_cast<Value<int>*>(args->at(7)))->value);
        hotelRoom->setChildrenBed((static_cast<Value<bool>*>(args->at(8)))->value);
        return true;
    } else if(type==ACC_TYPE::CABIN){
        // Build the luxuryLevel object first
        LuxuryLevel* luxuryLevel = new LuxuryLevel((static_cast<Value<bool>*>(args->at(6)))->value,
                                                   (static_cast<Value<bool>*>(args->at(7)))->value,
                                                   (static_cast<Value<bool>*>(args->at(8)))->value,
                                                   (static_cast<Value<bool>*>(args->at(9)))->value,
                                                   (static_cast<Value<string>*>(args->at(10)))->value);
        // Update the cabin accomodation
        Cabin* cabin = dynamic_cast<Cabin*>(accomodation);
        cabin->setID((static_cast<Value<int>*>(args->at(1)))->value);
        cabin->setNumberPeople((static_cast<Value<int>*>(args->at(2)))->value);
        cabin->setSize((static_cast<Value<int>*>(args->at(3)))->value);
        cabin->setBathroomWithBath((static_cast<Value<bool>*>(args->at(4)))->value);
        cabin->setBathroomWithBath(luxuryLevel);
        cabin->setBedrooms((static_cast<Value<int>*>(args->at(5)))->value);
        return true;
    }
    return false;
    
}

bool deleteAccomodation(int parkIndex, int accomodationIndex, VacationPark& vp){
    Park* p = vp.getParks()[parkIndex].get();
#ifdef DEBUG
    const size_t accSizeBefore = p->getAcccomodations().size();
#endif
    // Delete the accomodation of the memory first
    delete p->getAcccomodations()[accomodationIndex];
    // Then delete the pointer from the vector
    p->getAcccomodations().erase(p->getAcccomodations().begin()+accomodationIndex);
#ifdef DEBUG
    const size_t accSizeAfter = p->getAcccomodations().size();
    // Check if the accomodation has shrink
    assert(accSizeAfter<accSizeBefore);
#endif
    return true;
}

/// ownerAPI namespace end
///
///
}
