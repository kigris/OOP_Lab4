//
//  fileManagement.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 12/12/2022.
//

#ifndef fileManagement_hpp
#define fileManagement_hpp
// If compiled in Windows
#ifdef _WIN32
#include <Windows.h>
#include "dirent.h"
#
#else // else
#include <unistd.h>
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
bool deleteData(string fileSave);
#endif /* fileManagement_hpp */
