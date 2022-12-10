//
//  UI.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 02/12/2022.
//

#include "UI.hpp"


namespace owner{
/// Owner namespace begin
///
///
void accessAsOwner(VacationPark& vp) {
    // Display owner menu
    bool stayMenu = true;
    while (stayMenu) {
        int(&choices)[2]{menus::owner::displayOwnerMenu()};
        // Get the user's choice
        int choice = getUserChoice(choices[0], choices[1]);
        
        // Handle the user's choice
        switch (choice) {
            case 1:{
                // The user chose to register
                createPark(vp);
                break;}
            case 2:{
                editPark(vp);
                break;}
            case 3:{
                deletePark(vp);
                break;}
            case 4:{
                createAccomodation(vp);
                break;}
            case 5:{
                editAccomodation(vp);
                break;}
            case 6:{
                deleteAccomodation(vp);
                break;}
            case 7:
                // The user chose to go back
                stayMenu = false;
                cout<<endl;
                break;
            default:{
                cout<<"Invalid option..."<<endl;
                waitForEnter();
                break;}
        }
    }
}


void createPark(VacationPark& vp) {
    // Ask the customer for his user name
    string name;
    cout << "Enter the name: ";
    getline(cin, name);
    
    // Use regex to validate name
    if (!regex_match(name, nameRegex)) {
        cout << "Invalid name" << endl;
        waitForEnter();
        return;}
    
    // Check for duplicated name
    bool isDuplicated = ownerAPI::findPark(vp.getParks(), name);
    if(isDuplicated) {
        cout << "Duplicated name" << endl;
        waitForEnter();
        return;}
    
    string address;
    // Ask the customer for his address
    cout << "Enter the address: ";
    getline(cin, address);
    
    // Use regex to validate address
    if (!regex_match(address, addressRegex)){
        cout << "Invalid address" << endl;
        waitForEnter();
        return;}
    
    // Map of the luxuryLevel for an accomodation
    map<int, tuple<type_index, string>> servicePrompts {
        {1, {typeid(bool), "Has subtropic swimming pool? (0 no, 1 yes): "}},
        {2, {typeid(bool), "Has sports infrastructure? (0 no, 1 yes): "}},
        {3, {typeid(bool), "Has bowling alley? (0 no, 1 yes): "}},
        {4, {typeid(bool), "Has bicycle rent service? (0 no, 1 yes): "}},
        {5, {typeid(bool), "Has children paradise service? (0 no, 1 yes): "}},
        {6, {typeid(bool), "Has water bikes service? (0 no, 1 yes): "}},
    };
    
    // Get the inputs of all the common prompts
    map<int, void*>* serviceArgs = general::userPrompt(servicePrompts);
    if(serviceArgs==nullptr)
        return;
    
    Service* service = ownerAPI::createService(serviceArgs);
    delete serviceArgs; // Free up the memory of the pointer
    // Create the park
    ownerAPI::createPark(vp, name, address, service) ?
    cout << "Park created successfully" << endl:
    cout << "There was an error trying to create the park..." << endl;
    waitForEnter();
}


void editPark(VacationPark& vp) {
    // Ask the park to be edited
    Park* p = getPark(vp,"Select the park to edit: ");
    // If no correct park was selected
    if(p==nullptr)
        return;
    
    bool stayMenu = true;
    while(stayMenu){
        int(&choicesRange)[2]{menus::owner::parkUpdateMenu()};
        int choice = getUserChoice(choicesRange[0], choicesRange[1]);
        switch (choice) {
            case 1:{
                int statusCode = general::editFeature<Park*, PARK_EDIT_OPT>("Enter the new name: ", p, PARK_EDIT_OPT::NAME, &ownerAPI::updateParkFeature, nameRegex);
                if(statusCode==0)
                    cout<<"Name updated successfully"<<endl;
                else if(statusCode==1)
                    cout << "Error: new name same as old or there is another park using this name..."<<endl;
                waitForEnter(true);
                break;}
            case 2:{
                bool success = general::editFeature<Park*, PARK_EDIT_OPT>("Enter the new address: ", p, PARK_EDIT_OPT::ADDRESS, &ownerAPI::updateParkFeature, addressRegex);
                if(success)
                    cout<<"Address updated successfully"<<endl;
                waitForEnter(true);
                break;}
            case 3:{
                editParkService(p);
                break;}
            case 4:
                stayMenu = false;
                break;
            default:{
                cout << "Invalid choice" << endl;
                waitForEnter(true);
                break;}
        }
    }
}


void editParkService(Park* park) {
    cout<<"Enter 0 (does not have) or 1 (have) for each service"<<endl;
    
    string servicePrompts[] = {"Subtropic swimming pool: ", "Sports infrastructure: ", "Bowling alley: ", "Bicycle rent: ", "Children paradise: ", "Water bikes: "};
    size_t count = sizeof(servicePrompts)/sizeof(servicePrompts[0]);
    
    bool input[count];
    for(size_t i=0;i<count;i++){
        cout<<servicePrompts[i];
        int choice = getUserChoice(0, 1);
        if(choice!=-1){
            input[i] = (bool)choice;
        } else {
            cout << "Invalid choice" << endl;
            waitForEnter(true);
            return;}
    }
    
    ownerAPI::updateParkServices(park, input);
    cout<<"Service added successfully"<<endl;
    waitForEnter();
}


Park* getPark(VacationPark& vp, string displayText, int* index) {
    if(!existParks(vp)) return nullptr;
    cout << displayText << endl;
    int count{1};
    for(auto& p: vp.getParks()){
        cout << tabSpace() << count << ". " << p->getName() << endl;
        count++;
    }
    cout << "Enter the number of the park: ";
    
    int choice = getUserChoice(1, count);
    if(choice == -1){
        cout << "Invalid choice" << endl;
        waitForEnter();
        return nullptr;
    }
    if(index!=nullptr)
        *index = choice-1;
    return ownerAPI::getPark(vp, choice-1);
}


void deletePark(VacationPark& vp){
    // Ask the park to be deleted
    int index{-1};
    getPark(vp, "Select the park to delete: ", &index);
    if(index==-1)
        return;
    ownerAPI::deletePark(index, vp);
    cout<<"Park deleted successfully!"<<endl;
    waitForEnter();
}


void createAccomodation(VacationPark& vp){
    // Ask the park for the accomodation to be assigned
    Park* p = getPark(vp,"Select the park to assign the accomodation to: ");
    // If no correct park was selected or no parks created
    if(p==nullptr)
        return;
    ownerAPI::ACC_TYPE type;
    map<int, void*>* commonArgs = getAccomodationDetails(vp, nullptr, &type);
    if(commonArgs==nullptr)
        return;
    
    // Verify created
    bool isCreated = ownerAPI::createAccomodation(p->getAcccomodations(), commonArgs, type);
    // Check if it was created
    isCreated ? cout<<"HotelRoom created successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    
    // Release the memory for commonArgs
    delete commonArgs;
    waitForEnter();
}

bool existParks(VacationPark& vp){
    if(vp.getParks().size()==0){
        cout << "There are no parks created..." << endl;
        waitForEnter();
        return false;}
    return true;
}

Accomodation* getAccomodation(VacationPark& vp, string displayText, ownerAPI::ACC_TYPE* type, int* parkIndex, int* accomodationIndex) {
    // Check if parks and accomodations are created
    if(!existParks(vp)) return nullptr;
    bool existAccomodations = false;
    for(auto const& p : vp.getParks()){
        // If encounter one park that has accomodations break
        if(p->getAcccomodations().size()!=0){
            existAccomodations = true;
            break;}}
    if(!existAccomodations){
        cout << "There are no accomodations created..." << endl;
        waitForEnter();
        return nullptr;}
    
    cout << displayText << endl;
    // Map that holds the relationship between accomodations and parks
    // first int is the global index of an accomodation, second int is the index
    // of the park in which the accomodation is in, third int is the local index
    // of the accomodation in the park
    map<int, tuple<int, int>> parkAccomodationMap={};
    int parkCount{1};
    int globalAccomodationCount{1};
    string accomodationType{};
    for(const auto& p: vp.getParks()){
        int localAccomodationCount{1};
        for(auto const& a : p->getAcccomodations()){
            // Get type of accomodation
            accomodationType = (typeid(*a)==typeid(HotelRoom)) ?
            accomodationType = "Hotel Room" :
            accomodationType = "Cabin";
            // Print the current accomodation details
            cout << tabSpace() << globalAccomodationCount << ". " << "Accomodation (" <<
            accomodationType <<") with ID " << a->getId() <<" from park " << p->getName() << endl;
            parkAccomodationMap.emplace( globalAccomodationCount, make_tuple(parkCount, localAccomodationCount) );
            localAccomodationCount++;
            globalAccomodationCount++;}
        parkCount++;}
    
    cout << "Enter the number of the accomodation: ";
    int choice = getUserChoice(1, globalAccomodationCount);
    if(choice == -1){
        cout << "Invalid choice" << endl;
        waitForEnter();
        return nullptr;}
    
    // Get the indexes of park and local index accomodation from the map, remember to rest 1
    int parkInd = get<0>(parkAccomodationMap.at(choice))-1;
    int accomodationInd = get<1>(parkAccomodationMap.at(choice))-1;
    // If it's wanted to know the park index and the local index of the accomodation in that park
    if(accomodationIndex!=nullptr && parkIndex!=nullptr){
        *parkIndex = parkInd;
        *accomodationIndex = accomodationInd;}
    
    Accomodation* accomodation = ownerAPI::getAccomodation(vp, parkInd, accomodationInd);
    // Retrieve the type dynamically
    if(type!=nullptr){
        // Set the type of Hotelroom or Cabin
        *type= (typeid(*accomodation)==typeid(HotelRoom))?
        ownerAPI::ACC_TYPE::HOTELROOM:
        *type = ownerAPI::ACC_TYPE::CABIN;}
    return accomodation;
}


void editAccomodation(VacationPark& vp){
    ownerAPI::ACC_TYPE type;
    Accomodation* acc = getAccomodation(vp, "Select the number of the accomodation to edit: ", &type);
    if(acc==nullptr)
        return;
    
    map<int, void*>* commonArgs = getAccomodationDetails(vp, &type);
    if(commonArgs==nullptr)
        return;
    
    // Verify updated
    bool isUpdated = ownerAPI::updateAccomodation(acc, commonArgs, type);
    // Check if it was updated
    isUpdated ? cout<<"Accomodation updated successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    waitForEnter();
    delete commonArgs; // Release the memory for commonArgs
}

void deleteAccomodation(VacationPark& vp){
    int parkIndex{0};
    int accomodationIndex{0};
    Accomodation* acc = getAccomodation(vp, "Select the number of the accomodation to delete: ", nullptr, &parkIndex, &accomodationIndex);
    if(acc==nullptr)
        return;
    
    // Verify deleted
    bool isDeleted = ownerAPI::deleteAccomodation(parkIndex, accomodationIndex, vp);
    // Check if it was deleted
    isDeleted ? cout<<"Accomodation deleted successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    waitForEnter();
}

map<int, void*>* getAccomodationDetails(VacationPark& vp, ownerAPI::ACC_TYPE* type, ownerAPI::ACC_TYPE* typeRet){
    // Ask the owner for the id of the accomodation
    cout << "Enter the ID of the accomodation: ";
    int id = getUserChoice(0);
    
    // Check valid answer
    if (id == -1)
    {cout << "Invalid ID" << endl;
        waitForEnter();
        return nullptr;}
    
    // Check for duplicated name
    bool isDuplicated = ownerAPI::findAccomodation(vp.getParks(), id);
    if(isDuplicated) {
        cout << "Duplicated ID" << endl;
        waitForEnter();
        return nullptr;
    }
    
    // Map of the common prompts for an accomodation
    map<int, tuple<type_index, string>> accomodationPrompts {
        {2, {typeid(int), "Size (positive number): "}},
        {3, {typeid(int), "Maximum number of people (positive number): "}},
        {4, {typeid(bool), "Bathroom with bath? (0 no, 1 yes): "}},
    };
    
    // Get the inputs of all the common prompts
    map<int, void*>* commonArgs = general::userPrompt(accomodationPrompts);
    if(commonArgs==nullptr)
        return nullptr;
    // Emplace the id into the commonArgs
    commonArgs->emplace(1, new Value<int>{id});
    
    int typeAccomodation{0};
    if(type==NULL){
        cout << "Enter the type of the accomodation: "<<endl
        << "1. HotelRoom"<<endl<<"2. Cabin"<<endl<<
        "Enter your choice: ";
        typeAccomodation = getUserChoice(1,2);
        
        // Check valid answer
        if (typeAccomodation == -1)
        {cout << "Invalid ID" << endl;
            waitForEnter();
            return nullptr;}
    } else{
        typeAccomodation = (int)(*type);
    }
    
    // Hotelroom type
    int index{0};
    if(typeAccomodation==1){
        if(typeRet!=nullptr)
            *typeRet = ownerAPI::ACC_TYPE::HOTELROOM;
        // Map of the prompts for a hotelroom
        map<int, tuple<type_index, string>> hotelPrompts {
            {5, {typeid(int), "Floor (positive number): "}},
            {6, {typeid(string), "Location (text): "}},
            {7, {typeid(int), "Number of beds (positive number): "}},
            {8, {typeid(bool), "Children bed? (0 no, 1 yes): "}},
        };
        auto hotelArgs = general::userPrompt(hotelPrompts);
        if(hotelArgs==nullptr)
            return nullptr;
        // Merge hotelArgs into commonArgs
        commonArgs->insert(hotelArgs->begin(), hotelArgs->end());
        // Free dyanmic memory because it's not needed anymore
        delete hotelArgs;
        index = 9;
    } else {
        if(typeRet!=nullptr)
            *typeRet = ownerAPI::ACC_TYPE::CABIN;
        // Map of the prompts for a cabin
        map<int, tuple<type_index, string>> cabinPrompts {
            {5, {typeid(int), "Number of bedrooms (positive number): "}},
        };
        auto cabinArgs = general::userPrompt(cabinPrompts);
        if(cabinArgs==nullptr)
            return nullptr;
        // Merge cabinArgs into commonArgs
        commonArgs->insert(cabinArgs->begin(), cabinArgs->end());
        // Free dyanmic memory because it's not needed anymore
        delete cabinArgs;
        index = 6;
    }
    
    // Map of the luxuryLevel for an accomodation
    map<int, tuple<type_index, string>> luxuryPrompts {
        {index, {typeid(bool), "Has BBQ? (0 no, 1 yes): "}},
        {index+1, {typeid(bool), "Has surround system? (0 no, 1 yes): "}},
        {index+2, {typeid(bool), "Has breakfast service? (0 no, 1 yes): "}},
        {index+3, {typeid(bool), "Has cleaning service? (0 no, 1 yes): "}},
        {index+4, {typeid(string), "Accomodation kind (text): "}},
    };
    
    // Get the inputs of all the common prompts
    map<int, void*>* luxuryArgs = general::userPrompt(luxuryPrompts);
    if(luxuryArgs==nullptr)
        return nullptr;
    // Merge luxuryArgs into commonArgs
    commonArgs->insert(luxuryArgs->begin(), luxuryArgs->end());
    
    return commonArgs;
}


/// Owner namespace end
/// Owner namespace end
/// Owner namespace end
}


namespace customer{
/// Customer  namespace begin
/// Customer  namespace begin
/// Customer  namespace begin
void accessAsCustomer(VacationPark& vp) {
    // Display the customer menu
    bool stayMenu = true;
    while (stayMenu) {
        menus::displayCustomerMenu();
        // Get the user's choice
        int choice = getUserChoice(1, 3);
        
        // Handle the user's choice
        switch (choice) {
            case 1:{
                // The user chose to register
                registerCustomer(vp);}
                break;
            case 2:{
                // The user chose to login
                string username{};
                Customer* customer = loginCustomer(username, vp);
                
                if (customer) {
                    // The user logged in successfully
                    // Show the customer actions menu
                    bool shouldLogOut = false;
                    while (!shouldLogOut) {
                        menus::displayCustomerLoginMenu(customer->getName());
                        
                        // Create a map of functions that will handle the user's choice
                        std::map<int, std::function<void()>> choices = {
                            {1, [&]() { editCustomer(customer, vp); }},
                            {2, [&]() { createBooking(vp, customer); }},
                            //                            {3, [&]() { searchBookings(); }},
                            //                                                        {4, [&]() { bookAccommodations(); }},
                            //                            {5, [&]() { editBookings(); }},
                            //                            {6, [&]() { shouldLogOut = true; }}
                        };
                        
                        // Get the user's choice
                        int innerChoice = getUserChoice(1, 6);
                        // If choice is invalid
                        if(innerChoice == -1){
                            cout<<"Invalid choice..."<<endl;
                            waitForEnter();
                        }
                        if(innerChoice ==6)
                            shouldLogOut = true;
                        // Handle the user's choice
                        if (choices.count(innerChoice) > 0) {
                            choices[innerChoice]();}
                    }
                } else {
                    cout<<"User not found..."<<endl;
                    waitForEnter();}
                break;}
            case 3:
                // The user chose to go back
                stayMenu = false;
                break;
            default:{
                cout<<"Invalid option..."<<endl;
                waitForEnter();
                break;}
        }
    }
    
}


void registerCustomer(VacationPark& vp){
    string name, address, email;
    bool hasCustomerDetails = getCustomerDetails(vp, name, address, email);
    if(hasCustomerDetails){
        customerAPI::createCustomer(vp, name, address, email);
        // Print a success message
        cout << "Customer registered successfully" << endl;
        waitForEnter();
    }
}


Customer* loginCustomer(string& username, VacationPark& vp) {
    // Ask the customer for his user name
    cout << "Enter your name: ";
    string name;
    getline(cin, name);
    
    // Use regex to validate name
    if (!regex_match(name, nameRegex))
    {
        cout << "Invalid name" << endl;
        waitForEnter();
        return nullptr;
    }
    // Check if the user name exists
    Customer* c{nullptr};
    bool userExist = customerAPI::findCustomer(vp.getCustomers(), name, c);
    if(userExist) {
        return c;
    }
    return nullptr;
}


void editCustomer(Customer*& customer, VacationPark& vp) {
    string name, address, email;
    bool hasCustomerDetails = getCustomerDetails(vp, name, address, email);
    if(hasCustomerDetails && customerAPI::updateCustomer(customer, name, address, email)){
        // Print a success message
        cout << "Customer edited successfully" << endl;
        waitForEnter();
    }
}


bool getCustomerDetails(VacationPark& vp,string& name, string& address, string& email){
    // Ask the customer for his user name
    cout << "Enter your name: ";
    getline(cin, name);
    
    // Use regex to validate name
    if (!regex_match(name, nameRegex))
    {
        cout << "Invalid name" << endl;
        waitForEnter();
        return false;
    }
    
    // Check for duplicated name
    bool isDuplicated = customerAPI::findCustomer(vp.getCustomers(), name);
    if(isDuplicated) {
        cout << "Duplicated name" << endl;
        waitForEnter();
        return false;
    }
    
    // Ask the customer for his address
    cout << "Enter your address: ";
    getline(cin, address);
    
    // Use regex to validate address
    if (!regex_match(address, addressRegex))
    {
        cout << "Invalid address" << endl;
        waitForEnter();
        return false;
    }
    
    // Ask the customer for his address
    cout << "Enter your email: ";
    getline(cin, email);
    
    // Use regex to validate email
    regex emailRegex(R"(^[a-zA-Z0-9.!#$%&’*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\.[a-zA-Z0-9-]+)*\.[a-zA-Z]{2,}$)");
    if (!regex_match(email, emailRegex))
    {
        cout << "Invalid email" << endl;
        waitForEnter();
        return false;
    }
    
    return true;
}

void createBooking(VacationPark& vp, Customer* customer) {
    //    vp.getBookings().emplace_back(<#_Args &&__args...#>);
}
/// Customer namespace end
/// Customer namespace end
/// Customer namespace end
}

namespace general{
/// General namespace begin
/// General namespace begin
/// General namespace begin
template<typename T, typename U> int editFeature(string textDisplay, T object, U opt, bool (*func)(T, string, U), const regex re) {
    cout<<textDisplay<<endl;
    string input;
    getline(cin, input);
    // If regex is not empty
    if(!regex_match("", re)){
        // Check the input
        if(!regex_match(input, re)){
            cout<<"Invalid input..."<<endl;
            return -1;
        }
    }
    int returnCode = func(object, input, opt) ?  0 :  1;
    return returnCode;
}

map<int, void*>* userPrompt(map<int, tuple<type_index, string>>& prompts){
    map<int, void*>* args = new map<int, void*>();
    uint counter=0;
    for(auto it=prompts.cbegin(); it!=prompts.cend();it++){
        counter=it->first;
        cout<<get<1>(it->second); // Print the text
        // Get the type of the key
        const type_index& typeInd = get<0>(it->second);
        int answer{};
        // If the type is an integer, means that we need to catch a positive integer
        if(typeInd==typeid(int)){
            answer = getUserChoice(0);
            if (answer==-1){
                cout << "Invalid answer..." << endl;
                waitForEnter();
                return nullptr;}
            // Create the wrapper container that will contain the value itself
            auto value = new Value<int>{answer};
            // Insert the type of the value and the value itself,
            // a temporary object will be created and then copied into the container
            args->insert({ counter, value });
        }
        // If the type is a boolean, means that we need to catch a boolean value
        if(typeInd==typeid(bool)){
            answer = getUserChoice(0,1);
            if (answer==-1){
                cout << "Invalid answer..." << endl;
                waitForEnter();
                return nullptr;}
            // Create the wrapper container that will contain the value itself
            auto value = new Value<bool>{(bool)answer};
            // Emplace will create the object direct in place
            args->emplace(counter, value);
        }
        // If the type is a string, means that we need to catch a string value
        if(typeInd==typeid(string)){
            string answer;
            getline(cin, answer);
            
            if (!regex_match(answer, stringRegex)){
                cout << "Invalid answer..." << endl;
                waitForEnter();
                return nullptr;}
            // Create the wrapper container that will contain the value itself
            auto value = new Value<string>{(string)answer};
            // Emplace will create the object direct in place
            args->emplace(counter, value);
        }
        counter++;
    }
    return args;
}

/// General namespace end
///
///
}
