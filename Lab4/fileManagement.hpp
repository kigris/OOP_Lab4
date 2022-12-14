//
//  fileManagement.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 12/12/2022.
//

#ifndef fileManagement_hpp
#define fileManagement_hpp


#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif
#include <string>
#include <fstream>
#include <sstream>
#include "vacationParkAPI.hpp"
#include <filesystem>
using namespace std;

bool storeCurrentInformation(VacationPark& vp, string& name);
bool loadData(VacationPark& vp, string fileSave);
vector<string> getSaveNames();
bool deleteData(const std::string& saveName);
#endif /* fileManagement_hpp */
