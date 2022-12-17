//
//  customerAPI.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 29/11/2022.
//

#include "vacationParkAPI.hpp"

namespace ownerAPI{
/// ownerAPI namespace begin
/// ownerAPI namespace begin
/// ownerAPI namespace begin
bool findAccomodation(vector<unique_ptr<Park>>& parks, int id){
    // Look over all the parks
    for(auto const& p : parks)
        // Look over all the accomodations of a park
        for(auto const& a : p->getAccomodations())
            if(a->getId() == id)
                return true;
    return false;
}

bool findAccomodation(vector<unique_ptr<Park>>& parks, int id, Accomodation*& accomodation){
    // Look over all the parks
    for(auto const& p : parks)
        // Look over all the accomodations of a park
        for(auto const& a : p->getAccomodations())
            if(a->getId() == id){
                accomodation = a;
                return true;
            }
    accomodation = nullptr;
    return false;
}

bool findPark(vector<unique_ptr<Park>>& parks, string parkName){
    for(auto const& p : parks)
        if(convToLower(p->getName()) == convToLower(parkName))
            return true;
    return false;
}

Park* getPark(VacationPark& vp, int index, bool editMode){
    // Check if the park is reserved and user is in edit mode
    if(vp.getParks().at(index)->isReferenced() && editMode)
        return nullptr;
    // Otherwise return the park
    return vp.getParks().at(index).get();
}

Accomodation* getAccomodation(VacationPark& vp, int parkIndex, int accomodationIndex){
    return vp.getParks().at(parkIndex).get()->getAccomodations().at(accomodationIndex);
}

bool createPark(VacationPark& vp, string name, string address, Service* service){
    // We create the costumer
    unique_ptr<Park> park = make_unique<Park>(name, address, service);
    
    // Add the Costumer object to the list of costumers in vp
    try {
        // Add the park to the list of parks
        vp.getParks().emplace_back(move(park));
    } catch(exception){
        // If the park could not be added, we decrease the references
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
    // Check if the park has an accomodation that is booked
    for(auto a : parks[index]->getAccomodations())
        if(a->isReserved())
            return false;
    // If not, it can be deleted
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
    // If the accomodation is reserved, it can not be deleted
    if(p->getAccomodations()[accomodationIndex]->isReserved())
        return false;
#ifdef DEBUG
    const size_t accSizeBefore = p->getAccomodations().size();
#endif
    // Delete the accomodation of the memory first
    delete p->getAccomodations()[accomodationIndex];
    // Then delete the pointer from the vector
    p->getAccomodations().erase(p->getAccomodations().begin()+accomodationIndex);
#ifdef DEBUG
    const size_t accSizeAfter = p->getAccomodations().size();
    // Check if the accomodation has shrink
    assert(accSizeAfter<accSizeBefore);
#endif
    return true;
}

/// ownerAPI namespace end
/// ownerAPI namespace end
/// ownerAPI namespace end
}



namespace customerAPI{
/// customerAPI namespace begin
/// customerAPI namespace begin
/// customerAPI namespace begin
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
    customer=nullptr;
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

bool findBooking(vector<unique_ptr<Booking>>& bookings, string id){
    // Look over all the parks
    for(auto const& b : bookings)
        // Look over all the accomodations of a park
        if(b->getId() == id)
            return true;
    return false;
}

bool createBooking(VacationPark& vp, Customer* customer, Accomodation* accomodation, string id, bool activityPass, bool sportsPass, bool bicycleRent, bool swimmingPass){
    auto& bookings = vp.getBookings(); // Get a reference to bookings
    try{
        // Try to create and add the new booking
        unique_ptr<Booking> b = make_unique<Booking>(id, customer, activityPass, sportsPass, bicycleRent, swimmingPass);
        // Emplace the accomodation in the booking
        b->getAccomodations().emplace_back(accomodation);
        // Mark the accomodation as used
        accomodation->reserve();
        // Get booking's park
        Park* p = getBookingPark(vp, b.get());
        // Increase references to the park of the booking
        p->incrementReferences();
        // Emplace the booking in the bookings vector
        bookings.emplace_back(move(b));}
    catch(...){
        return false;}
    return true;
}

bool updateBooking(VacationPark& vp, Booking* booking, Accomodation* accomodation, bool parkReference){
    try{
        // Try to update the existing booking
        booking->getAccomodations().emplace_back(accomodation);
        // Mark the accomodation as used
        accomodation->reserve();
        // If the park needs to be references because one of its accomodations is reserved
        if(parkReference){
            // Get the park and increment its references
            Park* p{getBookingPark(vp, booking)};
            p->incrementReferences();}
    }
    catch(...){
        return false;}
    return true;
}

bool removeAccFromBooking(Booking* booking, Accomodation* accomodation, VacationPark& vp){
    auto& accomodations = booking->getAccomodations();
    try{
        // Try to delete the accomodation from the booking
        // First get the iterator of the new end of the vector
        auto last = remove(accomodations.begin(), accomodations.end(), accomodation);
        accomodations.erase(last, accomodations.end()); // Erase from there until the end
        // Mark the accomodation as unused
        accomodation->release();
        // If now the booking is empty, remove all the services booked
        if(booking->getAccomodations().empty()){
            booking->setSportsPass(false);
            booking->setActivityPass(false);
            booking->setSwimmingPass(false);
            booking->setBicycleRentPass(false);
            // Get the booking's park
            Park* p = getBookingPark(vp, booking);
            // Decrease references to the park of the booking
            p->decrementReferences();
            }
    }
    catch(...){
        return false;}
    return true;
}

Park* getBookingPark(VacationPark& vp, Booking* booking){
    Park* park{nullptr};
    bool found{false};
    // Iterate over all the parks
    for(auto const& p : vp.getParks()){
        // If have been found
        if(found) break; // break
        // Iterate over all the accomodations
        for(auto const& a : p->getAccomodations()){
            // Find the accomodation with the same id as the first accomodation of the booking
            if(a->getId()==booking->getAccomodations()[0]->getId()){
                park = p.get();
                found=true;
                break;}}}
    return park;
}

bool setBookingServices(Booking* booking, bool passes[4]){
    // Try to set the booking services
    try{
        booking->setSwimmingPass(passes[0]);
        booking->setSportsPass(passes[1]);
        booking->setActivityPass(passes[2]);
        booking->setBicycleRentPass(passes[3]);
    } catch(...){
        return false;
    }
    return true;
}

/// customerAPI namespace end
/// customerAPI namespace end
/// customerAPI namespace end
}


namespace employeeAPI {
/// employeeAPI namespace begin
/// employeeAPI namespace begin
/// employeeAPI namespace begin

bool deleteCustomer(int index, VacationPark& vp){
    Customer* customer = vp.getCustomers()[index].get();
    // Check if the customer has booked accomodations
    for(auto const& b : vp.getBookings())
        if(b->getCustomer()->getName() == customer->getName())
            return false;
    // If not, it can be deleted
    vp.getCustomers().erase(vp.getCustomers().begin()+index);
    return true;
}

bool deleteBooking(int index, VacationPark& vp){
    auto& bookings = vp.getBookings();
    try{
        // Try to delete the booking
        bookings.erase(bookings.begin()+index);
    }
    catch(...){
        return false;}
    return true;
}


/// employeeAPI namespace end
/// employeeAPI namespace end
/// employeeAPI namespace end
}
