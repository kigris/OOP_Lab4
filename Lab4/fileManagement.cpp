//
//  fileManagement.cpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 12/12/2022.
//

#include "fileManagement.hpp"

bool storeCurrentInformation(VacationPark& vp, string& name) {
    // Generate unique file name
    const string parentFolderName="data";
    string timeStamp = to_string(time(nullptr));
    name = timeStamp;
    const string saveFolder = parentFolderName+"/"+timeStamp;
    // Check if the directory exists
      if(!std::filesystem::exists(saveFolder.c_str())) {
        try {
          // Try to create the directory
          std::filesystem::create_directories(saveFolder.c_str());
        } catch (const std::filesystem::filesystem_error& ex) {
          std::cerr << "File Management: Failed to create save directory: " << ex.what() << "\n";
        }
      }

    string customersFN = saveFolder+"/customers.dat";
    
    // Open file for writing
    ofstream customersFS{customersFN,ios::out|ios::binary};
    // Save all the customers
    if(customersFS.is_open()){
        // Write the size of all the customers
        size_t size = vp.getCustomers().size();
        customersFS.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for(const auto& c : vp.getCustomers()){
            customersFS.write(reinterpret_cast<const char*>(c.get()), sizeof(Customer));
        }
    } else{
        customersFS.close();
        return false;}

    customersFS.close(); // Close the file
    
    string parksFN = saveFolder+"/parks.txt";
    string servicesFN = saveFolder+"/services.dat";
    string luxuryLevelFN = saveFolder+"/luxuryLevel.dat";
    string accomodationsFN = saveFolder+"/accomodations.txt";
    ofstream parksFS{parksFN, ios::out};
    ofstream servicesFS{servicesFN, ios::out|ios::binary};
    ofstream luxuryLevelFS{luxuryLevelFN, ios::out|ios::binary};
    ofstream accomodationsFS{accomodationsFN, ios::out};
    if(parksFS.is_open()){
        // Write the size of all the parks
        size_t size = vp.getParks().size();
        parksFS<<size<<endl;
        for(const auto& p : vp.getParks()){
            // Write parks
            parksFS<<p->getName()<<","<<p->getAddress()<<endl;
            // Write services
            servicesFS.write(reinterpret_cast<const char*>(p.get()->getService()), sizeof(Service));
            // Write accomodations size
            size_t accSize = p->getAcccomodations().size();
            parksFS<<accSize<<endl;
            // Write accomodations
            for(const auto& a : p->getAcccomodations()){
                // Get and write type of accomodation
                int typeAcc = (typeid(HotelRoom)==typeid(*a)) ? 0 : 1;
                accomodationsFS<<typeAcc<<endl;
                accomodationsFS<<a->getId()<<","<<a->isReserved()<<","<<a->getSize()<<","<<a->getNumberPeople()<<","<<
                a->getBathroomWithBath()<<",";
                // Write either Hotel or Cabin
                (typeAcc==0)?
                accomodationsFS<<((HotelRoom*)a)->getFloor()<<","<<((HotelRoom*)a)->getLocation()<<
                ","<<((HotelRoom*)a)->getNumberOfBeds()<<","<<((HotelRoom*)a)->getChildrenBed()<<endl:
                accomodationsFS<<((Cabin*)a)->getBedrooms()<<endl;
                // Write luxuryLevel
                luxuryLevelFS.write(reinterpret_cast<const char*>(a->getLuxuryLevel()), sizeof(LuxuryLevel));
            }
        }
    }else{
        parksFS.close();
        servicesFS.close();
        accomodationsFS.close();
        luxuryLevelFS.close();
        return false;}
    parksFS.close();
    servicesFS.close();
    accomodationsFS.close();
    luxuryLevelFS.close();
    
    string bookingsFN{saveFolder+"/bookings.txt"};
    ofstream bookingsFS{bookingsFN, ios::out};
    if(bookingsFS.is_open()){
        size_t bookingsSize = vp.getBookings().size();
        bookingsFS<<bookingsSize<<endl; // Write size of bookings
        for(const auto& b:vp.getBookings() ){
            // Write stack attributes, note that the customer name is written
            bookingsFS<<b->getId()<<","<<b->getCustomer()->getName()<<","<<b->getActivityPass()<<
            ","<<b->getSportsPass()<<","<<b->getBicycleRentPass()<<","<<b->getSwimmingPass()<<endl;
            // Read the accomodations size
            size_t accSize = b->getAccomodations().size();
            bookingsFS<<accSize<<endl; // Write the size
            // Write each accomodation's ID
            for(int i=0;i<accSize;i++)
                bookingsFS<<b->getAccomodations().at(i)->getId()<<endl;
        }
    } else {
        bookingsFS.close();
        return false;}
    bookingsFS.close();
    
    string classGIDsFN(saveFolder+"/classGIDs.dat");
    ofstream classGIDsFS{classGIDsFN, ios::out|ios::binary};
    if(classGIDsFS.is_open()){
        // Get global names of Customer
        size_t gNCSize = Customer::getGlobalNames().size();
        classGIDsFS.write(reinterpret_cast<const char*>(&gNCSize), sizeof(gNCSize));
        for(size_t i=0;i<gNCSize;i++){
            string gName = Customer::getGlobalNames().at(i);
            classGIDsFS.write(reinterpret_cast<const char*>(&gName), sizeof(gName));
        }
        // Get global names of Park
        size_t gNPSize = Park::getGlobalNames().size();
        classGIDsFS.write(reinterpret_cast<const char*>(&gNPSize), sizeof(gNPSize));
        for(size_t i=0;i<gNPSize;i++){
            string gName = Park::getGlobalNames().at(i);
            classGIDsFS.write(reinterpret_cast<const char*>(&gName), sizeof(gName));
        }
        // Get global ids of Accomodation
        size_t gIASize = Accomodation::getGlobalIDs().size();
        classGIDsFS.write(reinterpret_cast<const char*>(&gIASize), sizeof(gIASize));
        for(size_t i=0;i<gIASize;i++){
            int gID = Accomodation::getGlobalIDs().at(i);
            classGIDsFS.write(reinterpret_cast<const char*>(&gID), sizeof(gID));
        }
        // Get global ids of Bookings
        size_t gIBSize = Booking::getGlobalIDs().size();
        classGIDsFS.write(reinterpret_cast<const char*>(&gIBSize), sizeof(gIBSize));
        for(size_t i=0;i<gIBSize;i++){
            string gID = Booking::getGlobalIDs().at(i);
            classGIDsFS.write(reinterpret_cast<const char*>(&gID), sizeof(gID));
        }
    }else{
        classGIDsFS.close();
        return false;}
    classGIDsFS.close();
    return true;
}

bool loadData(VacationPark& vp, string fileSave){
    // Load customers
    string customersFN = "data/"+fileSave+"/customers.dat";
    ifstream customersFS{customersFN, ios::in|ios::binary};
    if(customersFS.is_open()){
        vp.getCustomers().clear();
        size_t size;
        customersFS.read(reinterpret_cast<char*>(&size), sizeof(size));
        for(size_t i=0;i<size;i++){
            unique_ptr<Customer> customer = make_unique<Customer>();
            customersFS.read(reinterpret_cast<char*>(customer.get()), sizeof(Customer));
            vp.getCustomers().emplace_back(move(customer));
        }
    } else{
        customersFS.close();
        return false;}
    customersFS.close();
    
    string parksFN = "data/"+fileSave+"/parks.txt";
    string servicesFN = "data/"+fileSave+"/services.dat";
    string luxuryLevelFN = "data/"+fileSave+"/luxuryLevel.dat";
    string accomodationsFN = "data/"+fileSave+"/accomodations.txt";
    ifstream parksFS{parksFN, ios::in};
    ifstream servicesFS{servicesFN, ios::in|ios::binary};
    ifstream luxuryLevelFS{luxuryLevelFN, ios::in|ios::binary};
    ifstream accomodationsFS{accomodationsFN, ios::in};
    if(parksFS.is_open()){
        // Clear the bookings first
        vp.getBookings().clear();
        // Then the parks
        vp.getParks().clear();
        // Read the size first
        string parkLine;
        getline(parksFS, parkLine); // Read 1st line
        size_t size = (size_t)atoi(parkLine.c_str()); // Get the size from 1st line
        vp.getParks().reserve(size); // Resize the parks vector
        for(size_t i=0;i<size;i++){
            string name, address;
            getline(parksFS, name, ',');
            getline(parksFS, address);
            getline(parksFS, parkLine);
            size_t accSize = (size_t)atoi(parkLine.c_str());
            string accLine;
            vector<Accomodation*> accomodations;
            for(size_t j=0;j<accSize;j++){
                getline(accomodationsFS, accLine);
                int typeAcc = atoi(accLine.c_str());
                getline(accomodationsFS, accLine);
                stringstream accLineSs(accLine);
                int id, size, numberOfPeople;
                bool isReserved, bathroomWithBath;
                accLineSs>>id;
                accLineSs.ignore();
                accLineSs>>isReserved;
                accLineSs.ignore();
                accLineSs>>size;
                accLineSs.ignore();
                accLineSs>>numberOfPeople;
                accLineSs.ignore();
                accLineSs>>bathroomWithBath;
                accLineSs.ignore();
                // If HotelRoom
                Accomodation* acc;
                // Read luxuryLevel
                LuxuryLevel* luxuryLevel = new LuxuryLevel();
                luxuryLevelFS.read(reinterpret_cast<char*>(luxuryLevel), sizeof(LuxuryLevel));
                if(typeAcc==0){
                    // Read the hotel room data from the line stream
                    int floor, numberOfBeds;
                    bool childrenBed;
                    string location;
                    accLineSs>>floor;
                    accLineSs.ignore();
                    getline(accLineSs, location, ',');
                    accLineSs>>numberOfBeds;
                    accLineSs.ignore();
                    accLineSs>>childrenBed;
                    accLineSs.ignore();
                    acc = new HotelRoom(id, size, numberOfPeople, bathroomWithBath, luxuryLevel, floor, location, numberOfBeds, childrenBed);
                } else {
                    int bedrooms;
                    accLineSs>>bedrooms;
                    accLineSs.ignore();
                    acc = new Cabin(id, size, numberOfPeople, bathroomWithBath, luxuryLevel, bedrooms);
                }
                if(isReserved) acc->reserve();
                accomodations.emplace_back(acc);
            }
            Service* service = new Service();
            servicesFS.read(reinterpret_cast<char*>(service), sizeof(Service));
            unique_ptr<Park> park = make_unique<Park>(name, address, service);
            park->setAcccomodations(accomodations);
            vp.getParks().emplace_back(move(park));
        }
    }else{
        parksFS.close();
        servicesFS.close();
        luxuryLevelFS.close();
        accomodationsFS.close();
        return false;}
    parksFS.close();
    servicesFS.close();
    luxuryLevelFS.close();
    accomodationsFS.close();
    
    string bookingsFN{"data/"+fileSave+"/bookings.txt"};
    ifstream bookingsFS{bookingsFN, ios::out};
    if(bookingsFS.is_open()){
        string bookLine;
        getline(bookingsFS, bookLine); // Read size of bookings
        size_t bookingsSize = (size_t)atoi(bookLine.c_str());
        vp.getBookings().reserve(bookingsSize);
        Customer* customer;
        for(size_t i=0;i<bookingsSize;i++){
            // Read stack attributes
            string ID, customerName;
            bool activityPass, sportsPass, bicycleRentPass, swimmingPass;
            getline(bookingsFS, ID, ',');
            getline(bookingsFS, customerName, ',');
            // Get customer pointer
            customerAPI::findCustomer(vp.getCustomers(), customerName, customer);
            getline(bookingsFS, bookLine);
            stringstream bookLineSs(bookLine);
            bookLineSs>>activityPass;
            bookLineSs.ignore();
            bookLineSs>>sportsPass;
            bookLineSs.ignore();
            bookLineSs>>bicycleRentPass;
            bookLineSs.ignore();
            bookLineSs>>swimmingPass;
            bookLineSs.ignore();
            // Read the accomodations size
            getline(bookingsFS, bookLine);
            size_t accSize = (size_t)atoi(bookLine.c_str());
            vector<Accomodation*> accomodations;
            Accomodation* acc;
            int accID;
            // Write each accomodation's ID
            for(int j=0;j<accSize;j++){
                // Read each accomodation ID
                getline(bookingsFS, bookLine);
                accID = atoi(bookLine.c_str());
                ownerAPI::findAccomodation(vp.getParks(), accID, acc);
                // And save it
                accomodations.push_back(acc);
            }
            unique_ptr<Booking> booking = make_unique<Booking>(ID, customer, accomodations, activityPass, bicycleRentPass, swimmingPass);
            vp.getBookings().emplace_back(move(booking));
        }
    } else {
        bookingsFS.close();
        return false;}
    bookingsFS.close();
    string classGIDsFN("data/"+fileSave+"/classGIDs.dat");
    ifstream classGIDsFS{classGIDsFN, ios::binary};
    if(classGIDsFS.is_open()){
        // Load global names of Customer
        size_t gNCSize;
        classGIDsFS.read(reinterpret_cast<char*>(&gNCSize), sizeof(gNCSize));
        vector<string> globalNC;
        for(size_t i=0;i<gNCSize;i++){
            string gName;
            classGIDsFS.read(reinterpret_cast<char*>(&gName), sizeof(gName));
            globalNC.emplace_back(gName);
        }
        Customer::setGlobalNames(globalNC);
        // Get global names of Park
        size_t gNPSize;
        classGIDsFS.read(reinterpret_cast<char*>(&gNPSize), sizeof(gNPSize));
        vector<string> globalNP;
        for(size_t i=0;i<gNPSize;i++){
            string gName;
            classGIDsFS.read(reinterpret_cast<char*>(&gName), sizeof(gName));
            globalNP.push_back(gName);
        }
        Park::setGlobalNames(globalNP);
        
        // Get global names of Accomodation
        size_t gIASize;
        classGIDsFS.read(reinterpret_cast<char*>(&gIASize), sizeof(gIASize));
        vector<int> globalIA;
        for(size_t i=0;i<gIASize;i++){
            int gID;
            classGIDsFS.read(reinterpret_cast<char*>(&gID), sizeof(gID));
            globalIA.push_back(gID);
        }
        Accomodation::setGlobalIDs(globalIA);
        
        // Get global names of Bookings
        size_t gIBSize;
        classGIDsFS.read(reinterpret_cast<char*>(&gIBSize), sizeof(gIBSize));
        vector<string> globalIB;
        for(size_t i=0;i<gIBSize;i++){
            string gID;
            classGIDsFS.read(reinterpret_cast<char*>(&gID), sizeof(gID));
            globalIB.push_back(gID);
        }
        Booking::setGlobalIDs(globalIB);
    }else{
        classGIDsFS.close();
        return false;}

    classGIDsFS.close();
    return true;
}

vector<string> getSaveNames(){
    // Get a list of folders with the data
    vector<string> files{}; // Store all the folders data here
    const char *dir_name = "data"; // Folder to search in
#ifdef _WIN32
    // Windows version
    WIN32_FIND_DATA fd;
    HANDLE hFind = FindFirstFile(dir_name, &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Compare to ignore current dir (.) or parent dir (..)
            // Ignore temporary folders that start with .something
            if (strcmp(fd.cFileName, ".") == 0 ||
                strcmp(fd.cFileName, "..") == 0 ||
                fd.cFileName[0] == '.')
                continue; // ignore them

            files.push_back(fd.cFileName); // otherwise push them
        } while (FindNextFile(hFind, &fd));

        FindClose(hFind);
    } else {
        cout << "Error: Directory " << dir_name << " not found" << endl;
    }
#else
    DIR* dir = opendir(dir_name);
    if (dir != nullptr) {
        struct dirent *entry; // Save directory properties here
        // While there are more directories to read
        while ((entry = readdir(dir)) != nullptr) {
            // Compare to ignore current dir (.) or parent dir (..)
            // Ignore temporary folders that start with .something
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0 ||
                entry->d_name[0] == '.')
                continue; // ignore them
            files.push_back(entry->d_name); // otherwise push them
        }
        closedir(dir); // Release the directory struct
    } else {
        cout<<"Error: Directory "<<dir_name<<" not found"<<endl;
    }
#endif
    sort(files.begin(), files.end(), greater<>());
    return files;
}

//bool deleteData(string saveName){
//    const string parentFolderName="data";
//    string fullPath = parentFolderName+"/"+saveName;
//    // Open the directory specified by dir_name
//    DIR* dir = opendir(fullPath.c_str());
//    // If the directory was successfully opened
//    if(dir != nullptr){
//        struct dirent* entry;
//        // Read the entries in the directory one by one
//        while((entry=readdir(dir))!=nullptr){
//            // Skip the current directory and the parent directory
//            if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0)
//                continue;
//            char path[512]; // directory name
//            snprintf(path, sizeof(path), "%s/%s", fullPath.c_str(), entry->d_name);
//            // If the entry is a directory, delete its contents recursively
//            if(entry->d_type==DT_DIR){
//                // If the file could not be deleted
//                if(!deleteData(path)){
//                    // Close the directory
//                    closedir(dir);
//                    return false;}
//            } else {
//                // If the entry is a file, delete it
//                if(unlink(path) < 0){
//                    // Close the directory
//                    closedir(dir);
//                    return false;}
//            }
//        }
//        // Close the directory
//        closedir(dir);
//        // Delete the directory
//        if(rmdir(fullPath.c_str()) < 0){
//            return false;
//        }
//        return true;
//    } else {
//        // The directory could not be opened
//        return false;
//    }
//}

bool deleteData(const std::string& saveName) {
    const std::string parentFolderName = "data";
    std::string fullPath = parentFolderName + "/" + saveName;

    // Open the directory specified by dir_name
    std::filesystem::directory_iterator dir(fullPath);
    // If the directory was successfully opened
    if (dir != std::filesystem::directory_iterator{}) {
        // Read the entries in the directory one by one
        for (const auto& entry : dir) {
            // Skip the current directory and the parent directory
            if (entry.path().filename() == "." || entry.path().filename() == "..") {
                continue;
            }
            // If the entry is a directory, delete its contents recursively
            if (is_directory(entry.path())) {
                // If the file could not be deleted
                if (!deleteData(entry.path().string())) {
                    // Close the directory
                    return false;
                }
            } else {
                // If the entry is a file, delete it
                if (!remove(entry)) {
                    return false;
                }
            }
        }
        // Delete the directory
        if (!filesystem::remove(fullPath)) {
            return false;
        }
        return true;
    } else {
        // The directory could not be opened
        return false;
    }
}
