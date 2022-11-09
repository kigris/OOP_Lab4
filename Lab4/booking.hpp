//
//  booking.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 09/11/2022.
//

#ifndef booking_hpp
#define booking_hpp

#include <stdio.h>
#include <string>
using std::string;

class Booking{
private:
    int id{0};
    string name;
public:
    int getId();
    void setId(int n_id);
};

#endif /* booking_hpp */
