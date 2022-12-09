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
        menus::displayOwnerMenu();
        // Get the user's choice
        int choice = getUserChoice(1, 6);
        
        // Handle the user's choice
        switch (choice) {
            case 1:{
                // The user chose to register
                createPark(vp);
                break;
            }
            case 2:{
                editPark(vp);
                break;
            }
            case 3:{
                deletePark(vp);
                break;
            }
            case 4:{
                createAccomodation(vp);
                break;
            }
            case 5:
                // The user chose to go back
                stayMenu = false;
                break;
            default:{
                cout<<"Invalid option..."<<endl;
                waitForEnter();
                break;
            }
        }
    }
}


void createPark(VacationPark& vp) {
    string name;
    // Ask the customer for his user name
    cout << "Enter the name: ";
    getline(cin, name);
    
    // Use regex to validate name
    if (!regex_match(name, nameRegex))
    {
        cout << "Invalid name" << endl;
        waitForEnter();
        return;
    }
    
    // Check for duplicated name
    bool isDuplicated = ownerAPI::findPark(vp.getParks(), name);
    if(isDuplicated) {
        cout << "Duplicated name" << endl;
        waitForEnter();
        return;
    }
    
    string address;
    // Ask the customer for his address
    cout << "Enter the address: ";
    getline(cin, address);
    
    // Use regex to validate address
    if (!regex_match(address, addressRegex))
    {
        cout << "Invalid address" << endl;
        waitForEnter();
        return;
    }
    
    // Create the park
    if(ownerAPI::createPark(vp, name, address)) {
        // Print a success message
        cout << "Park created successfully" << endl;
        waitForEnter();
    } else {
        // Print a error message
        cout << "There was an error trying to create the park..." << endl;
        waitForEnter();
    }
}


void editPark(VacationPark& vp) {
    // Ask the park to be edited
    cout << "Select the park to edit: " << endl;
    Park* p = getPark(vp);
    
    bool stayMenu = true;
    while(stayMenu){
        cout << "Want you want to do?"<<endl;
        cout << tabSpace() << "1. Update name"<<endl;
        cout << tabSpace() << "2. Update address"<<endl;
        cout << tabSpace() << "3. Update services"<<endl;
        cout << tabSpace() << "4. Exit"<<endl;
        int choice = getUserChoice(1, 4);
        switch (choice) {
            case 1:{
                bool success = general::editFeature<Park*, PARK_EDIT_OPT>("Enter the new name: ", p, PARK_EDIT_OPT::NAME, &ownerAPI::updateParkFeature, nameRegex);
                if(success)
                    cout<<"Name updated successfully"<<endl;
                else
                    cout << "Error: new name same as old or there is another park using this name..."<<endl;
                waitForEnter(true);
                break;
            }
            case 2:{
                bool success = general::editFeature<Park*, PARK_EDIT_OPT>("Enter the new address: ", p, PARK_EDIT_OPT::ADDRESS, &ownerAPI::updateParkFeature, addressRegex);
                if(success)
                    cout<<"Address updated successfully"<<endl;
                waitForEnter(true);
                break;
            }
            case 3:{
                editParkService(p);
                break;
            }
            case 4:
                stayMenu = false;
                break;
            default:{
                cout << "Invalid choice" << endl;
                waitForEnter(true);
                break;
            }
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
            return;
        }
    }
    
    ownerAPI::updateParkMultipleFeatures(park, input);
    cout<<"Service added successfully"<<endl;
    waitForEnter();
}


Park* getPark(VacationPark& vp, int* index) {
    int count{1};
    for(auto& p: vp.getParks()){
        cout << tabSpace() << count << ". " << p->getName() << endl;
        count++;
    }
    cout << "Enter your choice: " << endl;
    
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
    cout << "Select the park to delete: " << endl;
    int index{};
    getPark(vp, &index);
    ownerAPI::deletePark(index, vp);
    cout<<"Park deleted successfully!"<<endl;
    waitForEnter();
}

void createAccomodation(VacationPark& vp){
    // Ask the customer for the id of the accomodation
    cout << "Enter the ID of the accomodation: ";
    int id = getUserChoice(0);
    
    // Check valid answer
    if (id == -1)
    {cout << "Invalid ID" << endl;
        waitForEnter();
        return;}
    
    // Check for duplicated name
    bool isDuplicated = ownerAPI::findAccomodation(vp.getParks(), id);
    if(isDuplicated) {
        cout << "Duplicated ID" << endl;
        waitForEnter();
        return;
    }
    
    // Map of the common prompts for an accomodation
    map<int, tuple<type_index, string>> accomodationPrompts {
        {1, {typeid(int), "Size (positive number) : "}},
        {2, {typeid(int), "Maximum number of people (positive number) : "}},
        {3, {typeid(bool), "Bathroom with bath? (0 no, 1 yes) : "}},
    };
    
    map<int, tuple<type_index, void*>> commonArgs {};
    uint counter=0;
    for(auto it=accomodationPrompts.cbegin(); it!=accomodationPrompts.cend();it++){
        cout<<get<1>(it->second); // Print the text
        // Get the type of the key
        const type_index& typeInf = get<0>(it->second);
        int answer{};
        // If the type is an integer, means that we need to catch a positive integer
        if(typeInf==typeid(int)){
            answer = getUserChoice(0);
            if (answer==-1){
                cout << "Invalid answer..." << endl;
                waitForEnter();
                return;}
            // Create the wrapper container that will contain the value itself
            auto value = new Value<int>{answer};
            // Insert the type of the value and the value itself,
            // a temporary object will be created and then copied into the container
            commonArgs.insert({ counter, {typeInf,value} });
        }
        // If the type is an integer, means that we need to catch a boolean value
        if(typeInf==typeid(bool)){
            answer = getUserChoice(0,1);
            if (answer==-1){
                cout << "Invalid answer..." << endl;
                waitForEnter();
                return;}
            // Create the wrapper container that will contain the value itself
            auto value = new Value<bool>{(bool)answer};
            // Emplace will create the object direct in place
            commonArgs.emplace(counter, tuple<type_index, void*>{typeInf, value});
        }
    }
    cout << "Enter the type of the accomodation: "<<endl
    << "1. HotelRoom"<<endl<<"2. Cabin"<<endl<<
    "Enter your choice: ";
    int typeAccomodation = getUserChoice(1,2);
    
    // Check valid answer
    if (typeAccomodation == -1)
    {cout << "Invalid ID" << endl;
        waitForEnter();
        return;}
    
    cout<<"Accomodation created successfully"<<endl;
    waitForEnter();
}


/// Owner namespace end
///
///
}


namespace customer{
/// Customer  namespace begin
///
///
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
                registerCustomer(vp);
            }
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
                            //                            {2, [&]() { createBooking(vp); }},
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
                            choices[innerChoice]();
                        }
                    }
                } else {
                    cout<<"User not found..."<<endl;
                    waitForEnter();
                }
            }
                break;
            case 3:
                // The user chose to go back
                stayMenu = false;
                break;
            default:{
                cout<<"Invalid option..."<<endl;
                waitForEnter();
            }
                break;
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
///
///
}

namespace general{
/// General namespace begin
///
///
template<typename T, typename U> bool editFeature(string textDisplay, T object, U opt, bool (*func)(T, string, U), const regex re) {
    cout<<textDisplay<<endl;
    string input;
    getline(cin, input);
    // If regex is not empty
    if(!regex_match("", re)){
        // Check the input
        if(!regex_match(input, re)){
            cout<<"Invalid input..."<<endl;
            return false;
        }
    }
    return func(object, input, opt);
}
/// General namespace end
///
///
}
