//
//  fileManagement.hpp
//  Lab4
//
//  Created by Adrian Daniel Bodirlau on 12/12/2022.
//

#ifndef fileManagement_hpp
#define fileManagement_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include "vacationPark.hpp"
#include "park.hpp"
#include "hotelRoom.hpp"
#include "cabin.hpp"
#include "customer.hpp"
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include "vacationParkAPI.hpp"
#include <cstring>
#include <unistd.h>
#include <cstdio>
#include <filesystem>
using namespace std;

bool storeCurrentInformation(VacationPark& vp, string& name);
bool loadData(VacationPark& vp, string fileSave);
vector<string> getSaveNames();
bool deleteData(string fileSave);
#endif /* fileManagement_hpp */
