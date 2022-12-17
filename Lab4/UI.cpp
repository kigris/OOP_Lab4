//
//  UI.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 02/12/2022.
//

#include "UI.hpp"


namespace owner{
/// Owner namespace begin
/// Owner namespace begin
/// Owner namespace begin
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
                // Owner wants to create a park
                createPark(vp);
                break;}
            case 2:{
                // Owner wants to edit a park
                editPark(vp);
                break;}
            case 3:{
                // Owner wants to delete a park
                deletePark(vp);
                break;}
            case 4:{
                // Owner wants to create an accomodation
                createAccomodation(vp);
                break;}
            case 5:{
                // Owner wants to edit an accomodation
                editAccomodation(vp);
                break;}
            case 6:{
                // Owner wants to delete an accomodation
                deleteAccomodation(vp);
                break;}
            case 7:{
                // The owner wants to exit the main menu
                stayMenu = false;
                cout<<endl;
                break;
            }
            default:{
                // Display error message of invalid choice
                displayError("Error: Invalid choice...");
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
        displayError("Error: Invalid name");
        return;}
    
    // Check for duplicated name
    bool isDuplicated = ownerAPI::findPark(vp.getParks(), name);
    if(isDuplicated) {
        displayError("Error: Duplicated name");
        return;}
    
    string address;
    // Ask the customer for his address
    cout << "Enter the address: ";
    getline(cin, address);
    
    // Use regex to validate address
    if (!regex_match(address, addressRegex)){
        displayError("Error: Invalid address");
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
    // Free all the values allocated dynamically inside serviceArgs
    map<int, void*>::iterator it;
    for (it = serviceArgs->begin(); it != serviceArgs->end(); ++it)
      delete (Value<bool>*)(it->second);

    delete serviceArgs; // Free up the memory of the pointer
    // Create the park
    ownerAPI::createPark(vp, name, address, service) ?
    cout << "Park created successfully" << endl:
    cout << "There was an error trying to create the park..." << endl;
    waitForEnter();
}


void editPark(VacationPark& vp) {
    // Ask the park to be edited
    Park* p = getPark(vp,"Select the park to edit: ", nullptr, true);
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
        if(choice==-1){
            cout << "Invalid choice" << endl;
            waitForEnter(true);
            return;}
        input[i] = (bool)choice;
    }
    
    ownerAPI::updateParkServices(park, input);
    cout<<"Service added successfully"<<endl;
    waitForEnter();
}


Park* getPark(VacationPark& vp, string displayText, int* index, bool editMode) {
    if(!existParks(vp)) return nullptr;
    cout << displayText << endl;
    int count{0};
    for(auto& p: vp.getParks()){
        cout << tabSpace() << count+1 << ". " << p->getName() << endl;
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
    // Get the park
    Park* p = ownerAPI::getPark(vp, choice-1, editMode);
    if(p==nullptr)
        displayError("Error: Park has accomodations booked...");
    return p;
}


void deletePark(VacationPark& vp){
    // Ask the park to be deleted
    int index{-1};
    getPark(vp, "Select the park to delete: ", &index, true);
    if(index==-1)
        return;
    if(ownerAPI::deletePark(index, vp)){
        cout<<"Park deleted successfully!"<<endl;
        waitForEnter();}
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
    bool isCreated = ownerAPI::createAccomodation(p->getAccomodations(), commonArgs, type);
    // Check if it was created
    isCreated ? cout<<"HotelRoom created successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    // Release the memory allocated dynamically in commonArgs by getAccomodationDetails()
    map<int, void*>::iterator it;
    for (it = commonArgs->begin(); it != commonArgs->end(); ++it){
        if(typeid(int)==typeid(it->first))
            delete (Value<int>*)(it->second);
        if(typeid(bool)==typeid(it->first))
            delete (Value<bool>*)(it->second);
        if(typeid(string)==typeid(it->first))
            delete (Value<string>*)(it->second);
    }
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

bool existAccomodations(VacationPark& vp){
    bool existAccomodations = false;
    for(auto const& p : vp.getParks()){
        // If encounter one park that has accomodations break
        if(p->getAccomodations().size()!=0){
            existAccomodations = true;
            break;}}
    if(!existAccomodations){
        cout << "There are no accomodations created..." << endl;
        waitForEnter();
        return false;}
    return true;
}

Accomodation* getAccomodation(VacationPark& vp, string displayText, ownerAPI::ACC_TYPE* type, int* parkIndex, int* accomodationIndex) {
    // Check if parks and accomodations are created
    if(!existParks(vp)) return nullptr;
    if(!existAccomodations(vp)) return nullptr;
    
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
        for(auto const& a : p->getAccomodations()){
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
    if(acc->isReserved()){
        displayError("Error: Accomodation is reserved, can't be edited");
        return;}
    map<int, void*>* commonArgs = getAccomodationDetails(vp, &type);
    if(commonArgs==nullptr)
        return;
    
    // Verify updated
    bool isUpdated = ownerAPI::updateAccomodation(acc, commonArgs, type);
    // Release the memory allocated dynamically in commonArgs by getAccomodationDetails()
    map<int, void*>::iterator it;
    for (it = commonArgs->begin(); it != commonArgs->end(); ++it){
        if(typeid(int)==typeid(it->first))
            delete (Value<int>*)(it->second);
        if(typeid(bool)==typeid(it->first))
            delete (Value<bool>*)(it->second);
        if(typeid(string)==typeid(it->first))
            delete (Value<string>*)(it->second);
    }
    delete commonArgs; // Release the memory for commonArgs
    // Check if it was updated
    isUpdated ? cout<<"Accomodation updated successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    waitForEnter();
}

void deleteAccomodation(VacationPark& vp){
    int parkIndex{-1};
    int accomodationIndex{-1};
    Accomodation* acc = getAccomodation(vp, "Select the number of the accomodation to delete: ", nullptr, &parkIndex, &accomodationIndex);
    if(acc==nullptr)
        return;
    if(acc->isReserved()){
        displayError("Error: Accomodation is reserved, can't be deleted");
        return;}
    // Verify deleted
    bool isDeleted = ownerAPI::deleteAccomodation(parkIndex, accomodationIndex, vp);
    // Check if it was deleted
    isDeleted ? cout<<"Accomodation deleted successfully!"<<endl:
    cout<<"Error: this accomodation can not be deleted because it's booked..."<<endl;
    waitForEnter();
}

map<int, void*>* getAccomodationDetails(VacationPark& vp, ownerAPI::ACC_TYPE* type, ownerAPI::ACC_TYPE* typeRet){
    // Ask the owner for the id of the accomodation
    cout << "Enter the ID of the accomodation (positive number): ";
    int id = getUserChoice(0);
    
    // Check valid answer, if not return nullptr
    if(checkError(id, -1, "Error: Invalid ID")) return nullptr;
    
    // Check for duplicated name
    bool isDuplicated = ownerAPI::findAccomodation(vp.getParks(), id);
    // Check valid answer, if not return nullptr
    if(checkError(isDuplicated, true, "Error: Duplicated ID")) return nullptr;
    
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
        if(checkError(typeAccomodation, -1, "Error: Invalid type...")) return nullptr;
    }   else
        typeAccomodation = (int)(*type);
    
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
        map<int, void*>* hotelArgs = general::userPrompt(hotelPrompts);
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
    delete luxuryArgs; // Free up the luxuryArgs
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
                loginCustomerMenu(vp);
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


void registerCustomer(VacationPark& vp, bool employeeMode){
    string name, address, email;
    bool hasCustomerDetails = getCustomerDetails(vp, name, address, email, employeeMode);
    if(hasCustomerDetails){
        customerAPI::createCustomer(vp, name, address, email);
        // Print a success message
        cout << "Customer registered successfully" << endl;
        waitForEnter();
    }
}

void loginCustomerMenu(VacationPark& vp){
    string username{};
    Customer* customer = loginCustomer(username, vp);
    
    if (customer) {
        // The user logged in successfully
        while (true) {
            // Show the customer actions menu
            int(&choices)[2]{menus::displayCustomerLoginMenu(customer->getName())};
            // Get the user's choice
            int choice = getUserChoice(choices[0], choices[1]);
            // If choice is invalid
            if(choice == -1){
                cout<<"Invalid choice..."<<endl;
                waitForEnter();
                return;}
            if(choice==choices[1]) return; // User want to leave
            // Create a map of functions that will handle the user's choice
            std::map<int, std::function<void()>> funcChoices = {
                {1, [&]() { editCustomer(customer, vp); }},
                {2, [&]() { createBooking(vp, customer); }},
                {3, [&]() { editBookings(vp, customer); }},
            };
            // Handle the user's choice
            if (funcChoices.count(choice) > 0) {
                funcChoices[choice]();}
        }
    } else {
        cout<<"Error: User not found..."<<endl;
        waitForEnter();}
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


void editCustomer(Customer*& customer, VacationPark& vp, bool employeeMode) {
    string name, address, email;
    bool hasCustomerDetails = getCustomerDetails(vp, name, address, email, employeeMode);
    if(hasCustomerDetails && customerAPI::updateCustomer(customer, name, address, email)){
        // Print a success message
        cout << "Customer edited successfully" << endl;
        waitForEnter();
    }
}


bool getCustomerDetails(VacationPark& vp,string& name, string& address, string& email, bool employeeMode){
    // Display appropiate message if employee mode
    employeeMode? cout << "Enter the name: ":cout << "Enter your name: ";
    getline(cin, name);
    
    // Use regex to validate name
    if (!regex_match(name, nameRegex)){
        cout << "Invalid name" << endl;
        waitForEnter();
        return false;}
    
    // Check for duplicated name
    bool isDuplicated = customerAPI::findCustomer(vp.getCustomers(), name);
    if(isDuplicated) {
        cout << "Duplicated name" << endl;
        waitForEnter();
        return false;
    }
    
    employeeMode? cout << "Enter the address: ":cout << "Enter your address: ";
    
    getline(cin, address);
    // Use regex to validate address
    if (!regex_match(address, addressRegex))
    {
        cout << "Invalid address" << endl;
        waitForEnter();
        return false;
    }
    
    // If a employee is creating this account
    employeeMode? cout << "Enter the email: ":cout << "Enter your email: ";
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

void createBooking(VacationPark& vp, Customer* customer, bool employeeMode) {
    if(!owner::existParks(vp)) return;
    if(!owner::existAccomodations(vp)) return;
    
    Accomodation* accomodation = getAccomodationFiltered(vp);
    if(accomodation==nullptr)
        return;
    // Generate ID for the booking
    string id = generateBookingID(customer);
    // If it's duplicated
    while(customerAPI::findBooking(vp.getBookings(), id))
        // Get another one
        id = generateBookingID(customer);
    
    // Create the booking without any services
    bool isCreated = customerAPI::createBooking(vp, customer, accomodation, id, false, false, false, false);
    string pronoun = employeeMode ? "The": "Your";
    isCreated ? cout<<pronoun<<" new booking with ID "<< id << " was created successfully!" << endl:
    cout<<"There was an error trying to create" << convToLower(pronoun) << " booking...";
    waitForEnter();
}

Accomodation* getAccomodationFiltered(VacationPark& vp, Park* park, Booking* booking, bool employeeMode){
    // If there exist a previous accomodation booked and park is needed to be restricted to the same park
    // that the previous accomodation is in
    if(park!=nullptr){
        cout<< "INFO: There are " << booking->getAccomodations().size() << " accomodations booked. " <<endl;
        cout<< "Limiting filter to accomodations of park "<<park->getName()<<"..."<<endl;}
    cout<<"---Accomodation filter---"<<
    endl<<"Enter the type of the accomodation: "<<endl
    << "1. HotelRoom"<<endl<<"2. Cabin"<<endl;
    // If an employee is accessing this function
    employeeMode ? cout<<"Enter the choice: " : cout<<"Enter your choice: ";
    // Get the user choice for the accomodation type
    int typeAccomodation = getUserChoice(1,2);
    if(checkError(typeAccomodation, -1, "Error: Invalid answer...")) return nullptr;
    
    // Map of the filter prompts
    map<int, tuple<type_index, string>> filterPrompts {
        {2, {typeid(int), "For how many people? (positive number): "}},
        {3, {typeid(bool), "Has BBQ? (0 no, 1 yes): "}},
        {4, {typeid(bool), "Has surround system? (0 no, 1 yes): "}},
        {5, {typeid(bool), "Has breakfast service? (0 no, 1 yes): "}},
        {6, {typeid(bool), "Has cleaning service? (0 no, 1 yes): "}}
    };
    // Get the inputs for all the filter prompts
    map<int, void*>* filterArgs = general::userPrompt(filterPrompts);
    // If one filter failed a nullptr is returned
    if(filterArgs==nullptr)
        return nullptr;
    // Add the type of accomodation to the filter arguments
    filterArgs->emplace(1, new Value<int>{typeAccomodation});
    // Filter the accomodations
    map<int, tuple<Accomodation*, Park*>>* accFiltered = filterAccomodations(filterArgs, vp, park);
    delete filterArgs; // Free the memory
    // If there are no accomodations that match the filters
    if(accFiltered->empty()){
        employeeMode ? cout<<"No accomodations have match the filters provided..."<<endl:
        cout<<"No accomodations have match your filters..."<<endl;
        waitForEnter();
        return nullptr;}
    
    employeeMode ? cout<<"\nHere are the accomodations that matched the filters provided"<<endl :
    cout<<"\nHere are the accomodations that matched your filters"<<endl;
    // Display the filtered accomodations
    string typeAccStr{ (typeAccomodation==1) ? "hotel room":"cabin" };
    // Iterator for the map
    map<int, tuple<Accomodation*, Park*>>::iterator it = accFiltered->begin();
    // Iterate through the map while displaying the accomodations
    while(it != accFiltered->end()){
        auto accomodation = get<0>(it->second);
        auto park = get<1>(it->second);
        cout<< tabSpace() << it->first << ". Accomodation (" << typeAccStr <<
        ") with ID " << accomodation->getId() << " from park " << park->getName() << endl;
        ++it;
    }
    // Get the user choice for the accomodation
    employeeMode ? cout<<"Enter the choice: " : cout<<"Enter your choice: ";
    
    int choice = getUserChoice(1, (int)accFiltered->size());
    if(checkError(choice, -1, "Error: Invalid answer...")) return nullptr;
    // Return the accomodation selected by the user
    auto acc = get<0>(accFiltered->at(choice));
    delete accFiltered;
    return acc;
}

void editBookings(VacationPark& vp, Customer* customer, bool employeeMode){
    if(!existBookings(vp, customer)) return;
    
    Booking* booking = getBookings(vp, customer, "\n---Select the booking to edit--- ");
    if(booking==nullptr) return; // Check that user got a booking to edit
    // Menu loop
    while (true) {
        // Display the manu and get range of choices
        int(&choices)[2]{menus::displayBookingMenu(booking->getId())};
        // Get the user choice
        int choice = getUserChoice(choices[0], choices[1]);
        // If the user choice is invalid, ask again
        if(checkError(choice, -1, "Error: Invalid answer...")) continue;
        if(choice==choices[1]) break; // User want to leave, break the loop
        // Create a map of functions that will handle the user's choice
        std::map<int, std::function<void()>> funcChoices = {
            {1, [&]() { addAccomodation(booking, vp, employeeMode); }},
            {2, [&]() { removeAccomodation(booking, vp, employeeMode); }},
            {3, [&]() { bookServices(booking, vp, employeeMode); }},
        };
        
        // Handle the user's choice
        if (funcChoices.count(choice) > 0)
            funcChoices[choice]();}
}

void addAccomodation(Booking* booking, VacationPark& vp, bool employeeMode){
    if(booking->getAccomodations().size()==3){
        cout << "Error: This booking has reached the maximun number of 3 accomodations booked."<<endl;
        waitForEnter();
        return;}
    // If there are no accomodations booked
    if(booking->getAccomodations().size()==0){
        // Do not restrict the accomodations to a park
        Accomodation* accomodation = getAccomodationFiltered(vp, nullptr, nullptr, employeeMode);
        if(accomodation==nullptr)
            return;
        // Update the booking with the new accomodation
        bool isUpdated = customerAPI::updateBooking(vp, booking, accomodation, true);
        isUpdated ? cout<<"Booking with ID "<< booking->getId() << " was updated successfully!" << endl:
        cout<<"There was an error trying to update your booking...";}
    else{ // Otherwise
        // Restrict the accomodations to the park of the other accomodations
        Park* park{customerAPI::getBookingPark(vp, booking)};
#ifdef DEBUG
        // Park cannot be null, because an accomodation must belong to a park
        assert(park!=nullptr);
#endif
        Accomodation* accomodation = getAccomodationFiltered(vp, park, booking, employeeMode);
        if(accomodation==nullptr) return;
        // Update the booking with the new accomodation
        bool isUpdated = customerAPI::updateBooking(vp, booking, accomodation);
        // Display feedback to the user
        isUpdated ? cout<<"Booking with ID "<< booking->getId() << " was updated successfully!" << endl:
        cout<<"There was an error trying to update your booking...";}
    waitForEnter();
}

void removeAccomodation(Booking* booking, VacationPark& vp, bool employeeMode){
    if(booking->getAccomodations().empty()){
        cout << "Error: This booking has no accomodations booked."<<endl;
        waitForEnter();
        return;}
    cout<<"\nAccomodations from booking with ID "<<booking->getId()<<endl;
    int accSize{1};
    string typeAccomodation;
    for(auto& a : booking->getAccomodations()){
        typeAccomodation = (typeid(HotelRoom)==typeid(*a))?"hotel room":"cabin";
        cout<<accSize<<". Accomodation ("<<typeAccomodation<<") with ID "<<a->getId()<<endl;
        accSize++;}
    employeeMode?cout<<"Select the accomodation to remove: ":
    cout<<"Select the accomodation you want to remove: ";
    int choice = getUserChoice(1, accSize);
    if(choice==-1){
        cout<<"Invalid choice..."<<endl;
        waitForEnter();
        return;}
    bool isDeleted = customerAPI::removeAccFromBooking(booking, booking->getAccomodations()[choice-1], vp);
    isDeleted ? cout<<"Accomodation removed successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    waitForEnter();
}

bool existBookings(VacationPark& vp, Customer* customer){
    bool existAccomodations = false;
    for(auto const& b : vp.getBookings()){
        if(b->getCustomer()->getName() == customer->getName()){
            // If we find a booking that belongs to a customer
            existAccomodations = true;
            break;}}
    if(!existAccomodations){
        cout << "You have no bookings created..." << endl;
        waitForEnter();
        return false;}
    return true;
}

Booking* getBookings(VacationPark& vp, Customer* customer, string displayText, int* index) {
    cout << displayText << endl;
    vector<Booking*> customerBookings{};
    int bookingCount{1};
    // Go through all the bookings that belong to this customer
    for(auto const& b : vp.getBookings()){
        if(b->getCustomer()->getName() == customer->getName()){
            customerBookings.push_back(b.get());
            cout<< bookingCount <<". Booking with ID " << b->getId() << endl;
            bookingCount++;}}
    
    cout << "Enter the number of the booking: ";
    int choice = getUserChoice(1, bookingCount);
    if(choice == -1){
        cout << "Invalid choice" << endl;
        waitForEnter();
        return nullptr;}
    
    if(index!=nullptr) *index = choice-1;
    return customerBookings.at(choice-1);
}

map<int, tuple<Accomodation*, Park*>>* filterAccomodations(map<int, void*>* args, VacationPark& vp, Park* park){
    // typeAccomodation will be 1 for HotelRoom and 2 for Cabin
    int typeAccomodation = (static_cast<Value<int>*>(args->at(1)))->value;
    int numberOfPeople = (static_cast<Value<int>*>(args->at(2)))->value;
    bool hasBBQ = (static_cast<Value<bool>*>(args->at(3)))->value;
    bool hasSurroundSystem = (static_cast<Value<bool>*>(args->at(4)))->value;
    bool hasBreakfastService = (static_cast<Value<bool>*>(args->at(5)))->value;
    bool hasCleaningService = (static_cast<Value<bool>*>(args->at(6)))->value;
    
    map<int, tuple<Accomodation*, Park*>>* filteredAcc = new map<int, tuple<Accomodation*, Park*>>{};
    int counter{1};
    for(auto const& p : vp.getParks()){
        // If park filtering is required for existing bookings with 1 or more accomodations
        if(park!=nullptr)
            // If the name of the park is different,
            if(!(park->getName()==p->getName()))
                continue; // skip it
        for(auto const a : p->getAccomodations()){
            // If accomodations is reserved
            if(a->isReserved()) continue; // skip it
            // If Customer is not looking for this room
            if((typeid(*a)==typeid(HotelRoom)&& typeAccomodation==2)
               || (typeid(*a)==typeid(Cabin)&& typeAccomodation==1))
                continue;
            // Evaluate all the filters
            bool f1 = a->getNumberPeople()>=numberOfPeople;
            bool f2 = a->getLuxuryLevel()->getBBQ() == hasBBQ;
            bool f3 = a->getLuxuryLevel()->getSurroundSystem() == hasSurroundSystem;
            bool f4 = a->getLuxuryLevel()->getBreakfastService() == hasBreakfastService;
            bool f5 = a->getLuxuryLevel()->getCleaningService() == hasCleaningService;
            // If all filters are meeted
            if(f1&&f2&&f3&&f4&&f5)
                filteredAcc->insert( {counter++, make_tuple(a,p.get())} );
        }
    }
    return filteredAcc;
}

string generateBookingID(Customer* customer){
    srand((int)time(NULL));
    int accPick = rand()%3;
    string strToMix{""};
    if(accPick==0)
        strToMix.append(customer->getAddress());
    else if(accPick==1)
        strToMix.append(customer->getName());
    else if(accPick==2)
        strToMix.append(customer->getMail());
    return randIDGen(::BOOKING_ID_LENGTH, strToMix);
}


void bookServices(Booking* booking, VacationPark& vp, bool employeeMode){
    if(booking->getAccomodations().empty()){
        cout<<"Error: This booking is empty!"<<endl;
        employeeMode?
        cout<<"It is needed to book at least one accomodation in order to be able to book services."<<endl:
        cout<<"You must book at least one accomodation in order to be able to book services."<<endl;
        waitForEnter();
        return;}
    Park* p = customerAPI::getBookingPark(vp, booking);
    bool hasSSP = p->getService()->getSubtropicSwimmingPool();
    bool hasSI = p->getService()->getSportsInfrastructure();
    bool hasBA = p->getService()->getBowlingAlley();
    bool hasBR = p->getService()->getBicycleRent();
    bool hasCP = p->getService()->getChildrenParadise();
    bool hasWB = p->getService()->getWaterBikes();
    cout<<"This booking consist of accomodations in park "<<p->getName()<<"."<<endl;
    cout<<"Park "<<p->getName()<<" has this features: "<<endl;
    cout<<tabSpace()<<"Subtropic swimming pool (swimming pass service): "<< (hasSSP ? "yes":"no") << endl;
    cout<<tabSpace()<<"Sports infrastructure (sports pass service): "<< (hasSI ? "yes":"no") << endl;
    cout<<tabSpace()<<"Bowling alley (activity pass service): "<< (hasBA ? "yes":"no") << endl;
    cout<<tabSpace()<<"Bicycle rent (bicycle rent pass service): "<< (hasBR ? "yes":"no") << endl;
    cout<<tabSpace()<<"Children paradise (activity rent pass): "<< (hasCP ? "yes":"no") << endl;
    cout<<tabSpace()<<"Water bikes (activity pass): "<< (hasWB ? "yes":"no") << endl;
    
    employeeMode?   cout<< "Now it can be decided which services, of those that the park has, it is wanted." <<endl:
    cout<< "Now you can decide which services, of those that the park has, you want." <<endl;
    cout<< "NOTICE: Answer with 0 if no and with 1 if yes." <<endl;
    waitForEnter();
    bool passes[4]{false};
    int choice{0};
    if(hasBA || hasWB || hasCP){
        cout<<"Book activity pass service? ";
        choice = getUserChoice(0, 1);
        if(choice==-1){
            cout<<"Invalid answer..."<<endl;
            waitForEnter();
            return;}
        passes[2]=choice;}
    if(hasSI){
        cout<<"Book sports pass service? ";
        choice = getUserChoice(0, 1);
        if(choice==-1){
            cout<<"Invalid answer..."<<endl;
            waitForEnter();
            return;}
        passes[1]=choice;}
    if(hasBR){
        cout<<"Book bicycle rent pass service? ";
        choice = getUserChoice(0, 1);
        if(choice==-1){
            cout<<"Invalid answer..."<<endl;
            waitForEnter();
            return;}
        passes[3]=choice;}
    if(hasSSP){
        cout<<"Book swimming pass service? ";
        choice = getUserChoice(0, 1);
        if(choice==-1){
            cout<<"Invalid answer..."<<endl;
            waitForEnter();
            return;}
        passes[0]=choice;}
    
    bool hasBookedServices = customerAPI::setBookingServices(booking, passes);
    hasBookedServices ? cout<<"Services booked successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    waitForEnter();
}


/// Customer namespace end
/// Customer namespace end
/// Customer namespace end
}


namespace employee{
/// Employee namespace begin
/// Employee namespace begin
/// Employee namespace begin


void accessAsEmployee(VacationPark& vp){
    while (true) {
        // Show the customer actions menu
        int(&choices)[2]{menus::displayEmployeeMenu()};
        // Get the user's choice
        int choice = getUserChoice(choices[0], choices[1]);
        // If choice is invalid, return
        if(checkError(choice, -1, "Invalid choice!")) return;
        if(choice==choices[1]) break; // User want to leave
        // Create a map of functions that will handle the user's choice
        std::map<int, std::function<void()>> funcChoices = {
            {1, [&]() { customer::registerCustomer(vp, true); }},
            {2, [&]() { editCustomer(vp); }},
            {3, [&]() { deleteCustomer(vp); }},
            {4, [&]() { createBooking(vp); }},
            {5, [&]() { editBooking(vp); }},
            {6, [&]() { deleteBooking(vp); }},
            {7, [&]() { owner::editAccomodation(vp); }},
        };
        // Handle the user's choice
        if (funcChoices.count(choice) > 0) {
            funcChoices[choice]();}
    }
}


Customer* getCustomer(VacationPark& vp, string displayText, int* index){
    cout<<displayText<<endl; // Show information text
    // Counter for the customers, starting at 1
    int customerCount{1};
    // Show all the customers
    for(auto& c : vp.getCustomers()){
        cout<<tabSpace()<<customerCount<<". "<< c->getName() <<endl;
        customerCount++;
    }
    cout<<"Enter your selection: ";
    // Get the user's choice
    int choice = getUserChoice(1, customerCount);
    // If the choice is invalid, return nullptr
    if(checkError(choice, -1, "Error: Invalid choice...")) return nullptr;
    // If the index is wanted
    if(index!=nullptr)
        *index = choice-1; // Set it
    // Return the customer at the index -1
    return vp.getCustomers()[choice-1].get();
}

void editCustomer(VacationPark& vp){
    if(vp.getCustomers().empty()){
        cout<<"There are no customers created..."<<endl;
        waitForEnter();
        return;}
    Customer* customer = getCustomer(vp, "These are all customers");
    if(customer==nullptr) return;
    customer::editCustomer(customer, vp, true);
}

void deleteCustomer(VacationPark& vp){
    if(vp.getCustomers().empty()){
        cout<<"There are no customers created..."<<endl;
        waitForEnter();
        return;}
    int index{0};
    Customer* customer = getCustomer(vp, "These are all customers", &index);
    if(customer==nullptr) return;
    bool wasDeleted = employeeAPI::deleteCustomer(index, vp);
    wasDeleted ? cout<<"Customer deleted successfully!"<<endl :
    cout<<"Error: Customer cannot be deleted because it has accomodations booked..."<<endl;
    waitForEnter();
}

void createBooking(VacationPark& vp){
    if(vp.getCustomers().empty()){
        cout<<"There are no customers created..."<<endl;
        waitForEnter();
        return;}
    Customer* customer = getCustomer(vp, "Select the customer to creake the booking for");
    if(customer==nullptr) return;
    
    customer::createBooking(vp, customer, true);
}

void editBooking(VacationPark& vp){
    if(vp.getBookings().empty()){
        cout<<"There are no bookings created..."<<endl;
        waitForEnter();
        return;}
    Customer* customer = getCustomer(vp, "Select the customer to edit the booking for");
    if(customer==nullptr) return;
    
    customer::editBookings(vp, customer, true);
}

void deleteBooking(VacationPark& vp){
    if(vp.getBookings().empty()){
        cout<<"There are no bookings created..."<<endl;
        waitForEnter();
        return;}
    Customer* customer = getCustomer(vp, "Select the customer to delete the booking for");
    if(customer==nullptr) return;
    int index {-1};
    Booking* booking = customer::getBookings(vp, customer, "\n---Select the booking to delete--- ", &index);
    if(booking==nullptr) return; // Check that user got a booking to edit
    bool isDeleted = employeeAPI::deleteBooking(index, vp);
    isDeleted?  cout<<"Booking deleted successfully!"<<endl:
    cout<<"There was an error..."<<endl;
    waitForEnter();
}

/// Employee namespace end
/// Employee namespace end
/// Employee namespace end
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
    // Map that holds the arguments to be collected
    map<int, void*>* args = new map<int, void*>();
    uint counter=0; // Counter being used to keep track of the order of the arguments
    // Iterate through the prompts given
    for(auto it=prompts.cbegin(); it!=prompts.cend();it++){
        counter=it->first; // Get the counter from the prompts
        cout<<get<1>(it->second); // Print the text
        // Get the type of the key
        const type_index& typeInd = get<0>(it->second);
        int answer{}; // Choice of the user
        // If the type is an integer, means that a integer value is expected
        if(typeInd==typeid(int)){
            answer = getUserChoice(0); // Get the choice of the user
            // Check if the answer is valid, otherwise return nullptr
            if(checkError(answer, -1, "Error: Invalid answer...")) return nullptr;
            // Create the wrapper container that will contain the value itself
            auto value = new Value<int>{answer};
            // Insert the type of the value and the value itself,
            // a temporary object will be created and then copied into the container
            args->insert({ counter, value });
        }
        // If the type is a boolean, means that a boolean value is expected
        if(typeInd==typeid(bool)){
            answer = getUserChoice(0,1); // Get the choice of the user
            // Check if the answer is valid, otherwise return nullptr
            if(checkError(answer, -1, "Error: Invalid answer...")) return nullptr;
            // Create the wrapper container that will contain the value itself
            Value<bool>* value = new Value<bool>{(bool)answer};
            // Emplace the object direct in place
            args->emplace(counter, value);
        }
        // If the type is a string, means that a string value is expected
        if(typeInd==typeid(string)){
            string answer; // String answer of the user
            getline(cin, answer); // Get the answer of the user
            // Check if the answer is valid, otherwise return nullptr
            if (!regex_match(answer, stringRegex)){
                displayError("Error: Invalid input...");
                return nullptr;}
            // Create the wrapper container that will contain the value itself
            auto value = new Value<string>{(string)answer};
            // Emplace will create the object direct in place
            args->emplace(counter, value);
        }
        counter++; // Increment the counter
    }
    return args;
}

void viewData(VacationPark& vp){
    // Check if there are any customers created
    if(vp.getCustomers().empty()){
        cout<<"\n\nThere are no customers created..."<<endl;
    } else {
        cout<<"\n\n---Customers("<<vp.getCustomers().size()<<")---"<<endl<<endl;
        // Costumers data
        for(auto const& customer: vp.getCustomers()){
            cout<<setw(16)<<left<<"Name"<<setw(24)<<left<<"Address"<<setw(20)<<left<<"Email"<<endl;
            // Print customer data using columns
            cout<<setw(16)<<left<<customer->getName();
            cout<<setw(24)<<left<<customer->getAddress();
            cout<<setw(20)<<left<<customer->getMail()<<endl;
        }
    }
    waitForEnter(); // Wait before showing parks data
    // Check if there are any parks created
    if(vp.getParks().empty()){
        cout<<"\n\nThere are no park areas created..."<<endl;
    } else{
        cout<<"\n\n---Parks("<<vp.getParks().size()<<")---"<<endl<<endl;
        // Print header
        for(auto const& park: vp.getParks()){
            cout<<setw(16)<<left<<"Name"<<setw(24)<<left<<"Address"<<setw(10)<<left<<"References"<<endl;
            cout<<setw(16)<<left<<park->getName();
            cout<<setw(24)<<left<<park->getAddress();
            cout<<setw(10)<<left<<park->getReferences()<<endl;
            // Print the park service
            cout<<setw(15)<<left<<"Servicess: "<<endl;
            Service service = *(park->getService());
            cout<<service<<endl;

            // Print the park's accommodations
            cout<<setw(15)<<left<<"Accommodations("<< park->getAccomodations().size()<<"): "<<endl;
            for(Accomodation* acc:park->getAccomodations()){
                // Check type of accommodation
                string stringToPrint;
                if(typeid(HotelRoom)==typeid(*acc)){
                    stringToPrint = "\tHotel Room:\n";
                    stringToPrint += ((HotelRoom*)acc)->toString();
                } else {
                    stringToPrint = "\tCabin\n";
                    stringToPrint += ((Cabin*)acc)->toString();
                }
                cout<<left<<stringToPrint<<endl;
            }
        }
    }
    waitForEnter(); // Wait before showing bookings data
    // Check if there are any bookings created
    if(vp.getBookings().empty()){
        cout<<"\n\nThere are no bookings created..."<<endl;
    } else{
        cout<<"\n\n---Bookings("<<vp.getBookings().size()<<")---"<<endl<<endl;
        // Print header
        for(auto const& b: vp.getBookings()){
            string activityPass = b->getActivityPass()?"Yes":"No";
            string sportsPass = b->getSportsPass()?"Yes":"No";
            string bicycleRentPass = b->getBicycleRentPass()?"Yes":"No";
            string swimmingPass = b->getSwimmingPass()?"Yes":"No";
            // Print header
            cout<<right<<setw(8)<<"ID"<<setw(16)<<"Customer"<<setw(16)<<"Activity Pass"<<
            setw(14)<<"Sports pass"<<setw(20)<<"Bicycle rent pass"<<setw(16)<<"Swimming Pass"<<endl;
            // Print booking data
            cout<<right<<setw(8)<<b->getId()<<setw(16)<<b->getCustomer()->getName()<<setw(16)<<activityPass<<
            setw(14)<<sportsPass<<setw(20)<<bicycleRentPass<<setw(16)<<swimmingPass<<endl;

            // Get accomodations of the booking
            for(auto const& acc: b->getAccomodations()){
                // Check type of accommodation
                string stringToPrint;
                if(typeid(HotelRoom)==typeid(*acc)){
                    stringToPrint = "\tHotel Room:\n";
                    stringToPrint += ((HotelRoom*)acc)->toString();
                } else {
                    stringToPrint = "\tCabin\n";
                    stringToPrint += ((Cabin*)acc)->toString();
                }
                cout<<left<<stringToPrint<<endl;
            }
        }
    }
    waitForEnter(); // Wait before exiting
}

/// General namespace end
/// General namespace end
/// General namespace end
}


namespace fileMngmt{
/// File Management namespace begin
/// File Management namespace begin
/// File Management namespace begin


string& getSaveName(int* countSaves){
    static string returnStr;
    returnStr = ""; // Reset it after each call
    vector<string> saves = getSaveNames();
    // If the number of saves is wanted to know
    if(countSaves!=nullptr)
        *countSaves = (int)saves.size();
    // If there are no data files, return
    if (saves.empty()) {
        return returnStr;
    }
    // Show the list of files
    cout << "---Saves list---" << endl;
    cout << "----Sorted from most recent to least recent-----" << endl;
    for (int i = 0; i < saves.size(); i++) {
        cout << tabSpace() << i + 1 << ". " << saves[i] << endl;}
    cout<<"Enter your choice: ";
    // Get the user's choice
    int choice = getUserChoice(1, (int)saves.size());
    if(choice==-1){
        displayError("Error: Invalid choice...");
        return returnStr;}
    // If the user's choice is valid, save that into the static string variable
    returnStr = saves[choice - 1]; // Return it
    return returnStr;
}

// Handle file management
void fileManagement(VacationPark& vp) {
    // File management loop
    while (true) {
        // Display file management menu
        int(&choices)[2]{menus::displayFileManagementMenu()};
        
        // Get user choice
        int choice = getUserChoice(choices[0], choices[1]);
        if(choice==-1){
            displayError("Error: Invalid choice...");
            continue;}
        if(choice==choices[1]) return;
        
        // Convert user choice to FileManagementOption enumerator
        FileManagementOption option = static_cast<FileManagementOption>(choice);
        
        // Handle user choice
        if (option == FileManagementOption::STORE_DATA) {
            // Store current information
            string saveName{};
            bool success = storeCurrentInformation(vp, saveName);
            success ? cout<<"Save with name: \""<< saveName <<"\" was created successfully!"<<endl:
            cout<<"Error: Something gone wrong trying to create your save. Check permissions...";
        } else if(option == FileManagementOption::LOAD_DATA) {
            int countSize{0};
            // Load information
            string saveName = getSaveName(&countSize);
            if(countSize==0){
                displayError("Error: There are no saves created...");
                continue;}
            if(saveName=="")
                continue;
            bool success = loadData(vp, saveName);
            success ? cout<<"Save with name: \""<< saveName <<"\" was loaded successfully!"<<endl:
            cout<<"Error: Something gone wrong trying to load your save. Check permissions...";
        } else {
            int countSize{0};
            // Delete information
            string saveName = getSaveName(&countSize);
            if(countSize==0){
                displayError("Error: There are no saves created...");
                continue;}
            if(saveName=="")
                continue;
            bool success = deleteData(saveName);
            success ? cout<<"Save with name: \""<< saveName <<"\" was deleted successfully!"<<endl:
            cout<<"Error: Something gone wrong trying to delete your save. Check permissions...";
        }
        waitForEnter();
    }
}


/// File Management namespace end
/// File Management namespace end
/// File Management namespace end
}
