//
//  fileManagement.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 12/12/2022.
//

#ifndef fileManagement_hpp
#define fileManagement_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "vacationParkAPI.hpp"
#include <unistd.h>
#include <filesystem>
using namespace std;

bool storeCurrentInformation(VacationPark& vp, string& name);
bool loadData(VacationPark& vp, string fileSave);
vector<string> getSaveNames();
bool deleteData(string fileSave);
#endif /* fileManagement_hpp */
