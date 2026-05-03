#include "pharmacy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


bool barcodeExists(const std::string& fileName, const std::string& barcode) {
    std::ifstream readBarcode(fileName);
    if(!readBarcode) {
        std::cerr<<"File not Opened"<<std::endl;
        return false;
    }

    std::string line;
    while(getline(readBarcode,line)) {
        std::stringstream ss(line);
        std::string tempBarcode,tempName,tempStock,tempPrice,tempDate;
        getline(ss,tempBarcode,',');
        getline(ss,tempName,',');
        getline(ss,tempStock,',');
        getline(ss,tempPrice,',');
        getline(ss,tempDate,',');
        
        if(tempBarcode==barcode) {
            return true;
        }
    }
    return false;
}



void addMedicine(const std::string& fileName,
                 const std::string& barcode, const std::string& name,
                 int stock, double price, const std::string& expiry) {

                    
                    if(!barcodeExists(fileName,barcode)) {
        
                    std::ofstream writeAddMedicine(fileName,std::ios::app);
if(!writeAddMedicine.is_open()) {
    std::cerr<<"File not Opened"<<std::endl;
    return;
}
writeAddMedicine<<barcode<<","<<name<<","<<stock<<","<<price<<","<<expiry<<std::endl;
                    }

                    else {
                        std::cerr<<"[WARNING] already registered"<<std::endl;
                        return;
                    }
                 }



void listMedicines(const std::string& fileName, const std::string& today) {
    std::ifstream readList(fileName);
    if(!readList.is_open()) {
        std::cerr<<"File not Opened"<<std::endl;
        return;
    }

    std::string line;
    while(getline(readList,line)) {
        std::stringstream ss(line);
         std::string tempBarcode,tempName,tempStock,tempPrice,tempDate;
        getline(ss,tempBarcode,',');
        getline(ss,tempName,',');
        getline(ss,tempStock,',');
        getline(ss,tempPrice,',');
        getline(ss,tempDate,',');
          std::cout << tempBarcode << " | "
                  << tempName << " | "
                  << "Stock:" << tempStock << " | "
                  << tempPrice << " TL | "
                  << "SKT:" << tempDate;

if (!tempDate.empty() && tempDate < today) {
            std::cout<<"[Expired]"<<std::endl;
        }
        std::cout<<"\n";
    }
}



void sellMedicine(const std::string& fileName,
                  const std::string& barcode, int qty,
                  const std::string& today) {
                    std::ifstream readSellMedicine(fileName);
                    std::ofstream writeSellMedicine("temp.txt");
                    if(!readSellMedicine.is_open() || !writeSellMedicine.is_open()) {
                        std::cerr<<"File not Opened"<<std::endl;
                        return;
                    }

                    std::string line;
                    bool found = false;
while(getline(readSellMedicine,line)) {
    std::stringstream ss(line);
    std::string tempBarcode,tempName,tempStock,tempPrice,tempDate;
        getline(ss,tempBarcode,',');
        getline(ss,tempName,',');
        getline(ss,tempStock,',');
        getline(ss,tempPrice,',');
        getline(ss,tempDate,',');
        

        int stock = std::stoi(tempStock);
        if(tempBarcode == barcode) {
            found = true;

        if (!tempDate.empty() && tempDate < today) {
            std::cout<<"[Expired]"<<std::endl;
            writeSellMedicine << line << '\n';
                continue;
        }

        if (!tempStock.empty() && stock < qty) {
            std::cout<<"[Invalid]"<<std::endl;
          writeSellMedicine<< line << '\n';
                continue;
        }

stock -= qty;
writeSellMedicine<<tempBarcode<<","<<tempName<<","<<stock<<","<<tempPrice<<","<<tempDate<<std::endl;
    }
        else {
          writeSellMedicine << line << '\n';
        }
                    }
                
                    readSellMedicine.close();
                    writeSellMedicine.close();
     
                    
if (!found) {
    std::cout << "[ERROR] Urun bulunamadi\n";
    remove("temp.txt");
    return;
}
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
     
            }


            
void checkExpired(const std::string& fileName, const std::string& today) {
        std::ifstream readList(fileName);
    if(!readList.is_open()) {
        std::cerr<<"File not Opened"<<std::endl;
        return;
    }

    std::string line;
    while(getline(readList,line)) {
        std::stringstream ss(line);
         std::string tempBarcode,tempName,tempStock,tempPrice,tempDate;
        getline(ss,tempBarcode,',');
        getline(ss,tempName,',');
        getline(ss,tempStock,',');
        getline(ss,tempPrice,',');
        getline(ss,tempDate,',');
        if (!tempDate.empty() && tempDate < today) {
            std::cout<<"[Expired]"<<std::endl;


          std::cout << tempBarcode << " | "
                  << tempName << " | "
                  << "Stock:" << tempStock << " | "
                  << tempPrice << " TL | "
                  << "SKT:" << tempDate;
        std::cout<<"\n";
      }
   }
}



void lowStock(const std::string& fileName, int threshold) {
            std::ifstream readList(fileName);
    if(!readList.is_open()) {
        std::cerr<<"File not Opened"<<std::endl;
        return;
    }

    std::string line;
    while(getline(readList,line)) {
        std::stringstream ss(line);
         std::string tempBarcode,tempName,tempStock,tempPrice,tempDate;
        getline(ss,tempBarcode,',');
        getline(ss,tempName,',');
        getline(ss,tempStock,',');
        getline(ss,tempPrice,',');
        getline(ss,tempDate,',');
        int stock = std::stoi(tempStock);
        if (!tempStock.empty() && stock < threshold) {
    
          std::cout << tempBarcode << " | "
                  << tempName << " | "
                  << "Stock:" << tempStock << " | "
                  << tempPrice << " TL | "
                  << "SKT:" << tempDate;
        std::cout<<"\n";
      }
   }
}



// TODO: temp dosya, barkod eşleşirse fiyatı güncelle
// TODO: remove + rename
void updatePrice(const std::string& fileName,
                 const std::string& barcode, double newPrice) {
        
     std::ifstream readUpdate(fileName);
     std::ofstream writeUpdate("temp.txt");
         if(!readUpdate.is_open() || !writeUpdate.is_open()) {
             std::cerr<<"File not Opened"<<std::endl;
                        return;
                    }

                    std::string line;
                    bool found = false;
while(getline(readUpdate,line)) {
    std::stringstream ss(line);
    std::string tempBarcode,tempName,tempStock,tempPrice,tempDate;
        getline(ss,tempBarcode,',');
        getline(ss,tempName,',');
        getline(ss,tempStock,',');
        getline(ss,tempPrice,',');
        getline(ss,tempDate,',');
        

        if(tempBarcode == barcode) {
            found = true;
writeUpdate<<tempBarcode<<","<<tempName<<","<<tempStock<<","<<newPrice<<","<<tempDate<<std::endl;
    }
        else {
            writeUpdate<<line<<std::endl;
        }
                    }
                
                    readUpdate.close();
                    writeUpdate.close();
                     if(!found) {
std::cerr<<"Barcode not Found"<<std::endl;
   remove("temp.txt"); 
    
return;
    }
                    
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
   
    
    }
            
                 

 