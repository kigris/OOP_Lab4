//
//  unitTesting.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 10/12/2022.
//

#include "unitTesting.hpp"

void testCreationAndDeletionParks(int numberOfParks) {
    cout<<"Creation and deletion of parks: Test begins..."<<endl;
    // This is for testing memory leaks
    VacationPark vacationPark("Wonderland Park", "Avenue 52, 1020, Oklahoma, US");
    // Create n parks
    for(int i = 0; i<numberOfParks; i++){
        string name="peter"+to_string(i);
        string address="testAddress";
        // Get the inputs of all the common prompts
        map<int, void*>* serviceArgs =  new map<int, void*>{
            {1, new Value<bool>(true)},
            {2, new Value<bool>(true)},
            {3, new Value<bool>(true)},
            {4, new Value<bool>(true)},
            {5, new Value<bool>(true)},
            {6, new Value<bool>(true)},
        };
        Service* service = ownerAPI::createService(serviceArgs);
        delete serviceArgs;
        // Create the park
        ownerAPI::createPark(vacationPark, name, address, service);
    }
    
    for(size_t i = vacationPark.getParks().size(); i-- != 0;)
    {
        ownerAPI::deletePark((int)i, vacationPark);
    }
    cout<<"Creation and deletion of parks: Test completed!"<<endl;
}
