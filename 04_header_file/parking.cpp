#include "parking.h"
#include <string>
#include <sstream>
#include <chrono>
#include <fstream>
#include <iostream>

int toMinutes(const std::string& time) {

int h,m;
char c;
std::stringstream ss(time);
ss>>h>>c>>m;
if (!(ss >> h >> c >> m) || c != ':')
    throw std::invalid_argument("Invalid format");

    std::chrono::minutes total = std::chrono::hours(h) + std::chrono::minutes(m);
    return total.count();
}

//*
//*
//*


bool isInside(const std::string& fileName, const std::string& plate) {
        std::ifstream readPlate(fileName);
    if(!readPlate) {
    std::cerr<<"File not opened"<<std::endl;
    return false;
}
std::string line;
while(getline(readPlate,line)) {
    std::stringstream ss(line);
    std::string numberPlate,login,exit;
    getline(ss,numberPlate,',');
    getline(ss,login,',');
    getline(ss,exit,',');

    if(numberPlate==plate && exit=="-") {
    return true;
    }
}
return false;
    }

//*
//*
//*

void enterParking(const std::string& fileName,
                  const std::string& plate, const std::string& spot,
                  const std::string& entryTime) {
         
    if (isInside(fileName, plate)) {
    std::cerr << "Plate already inside" << std::endl;
    return;
}
    
    std::ofstream writeParking(fileName,std::ios::app);
    if(!writeParking) {
        std::cerr<<"File Not Opened"<<std::endl;
        return;
    }          

    writeParking << plate << "," << spot << "," << entryTime << ",-" << ",0\n";

    std::cout << "[OK] " << plate << " entered → Spot: " << spot << std::endl;
                  }

//*
//*
//*
               
  void exitParking(const std::string& fileName,
                   const std::string& plate, const std::string& exitTime) {
std::ifstream readExit(fileName);
if(!readExit) {
    std::cerr<<"File not Opened"<<std::endl;
    return;
}

std::ofstream writeExit("temp.txt");
if(!writeExit) {
    std::cerr<<"File Not Opened"<<std::endl;
    return;
}
bool found = false;
std::string line;
while(getline(readExit,line)) {
    std::stringstream ss(line);
std::string p,spot,in,out,f;
getline(ss,p,',');
getline(ss,spot,',');
getline(ss,in,',');
getline(ss,out,',');
getline(ss,f,',');


if(p==plate && out=="-") {
    found = true;
    int exitmin= toMinutes(exitTime);
    int entrymin = toMinutes(in);
    int duration  = (exitmin-entrymin); 
    double fee =  duration * 1.5;
    
    writeExit<<p<<","<<spot<<","<<in<<","<<exitTime<<","<<fee<<std::endl;
}
else {
    writeExit<<line<<std::endl;
    
}
}

readExit.close();
writeExit.close();

if(!found) {
    std::cerr<<"Plate not Found"<<std::endl;
    remove("temp.txt");
    return;
}

    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
}
                
//*
//*
//*

void listParking(const std::string& fileName) {
std::ifstream readFile(fileName);
if(!readFile) {
    std::cerr<<"File Not Opened"<<std::endl;
    return;
}

std::string line;
while(getline(readFile,line)) {
std::stringstream ss(line);
std::string plate,spot,in,out,fee;
getline(ss,plate,',');
getline(ss,spot,',');
getline(ss,in,',');
getline(ss,out,',');
getline(ss,fee,',');

if(out=="-") {

    
std::cout<<plate<<","
         <<spot<<","
         <<in<<","
         <<"ICERDE"<<std::endl;
        }
    
         else {

std::cout<<plate<<","
         <<spot<<","
         <<in<<","
         <<out<<","
         <<fee<<" TL"
         <<std::endl;
    }

}

readFile.close();
}

//*
//*
//*

double dailyRevenue(const std::string& fileName) {

std::ifstream readFee(fileName);
if(!readFee) {
    std::cerr<<"File Not Opened"<<std::endl;
    return 0.0;
}
double total = 0;

std::string line;
while(getline(readFee,line)) {
std::stringstream ss(line);
std::string plate,spot,in,out,f;
getline(ss,plate,',');
getline(ss,spot,',');
getline(ss,in,',');
getline(ss,out,',');
getline(ss,f,',');


  if (!f.empty() && out != "-") {
            total += std::stod(f);
        }

}
readFee.close();
return total;
}

