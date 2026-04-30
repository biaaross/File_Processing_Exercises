#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>

void stockList(const std::string& fileName);
void addProduct(const std::string& fileName,const std::string& product,double price,int quantity);
void deleteProduct(const std::string& fileName,const std::string& target);
void updatePrice(const std::string& fileName,const std::string target,double newPrice);

int main() {

  std::string fileName = "stock.txt";

    addProduct(fileName, "Apple", 3.50, 150);
    addProduct(fileName, "Milk", 12.00, 80);
    addProduct(fileName, "Bread", 7.50, 200);
    addProduct(fileName, "Cheese", 65.00, 45);

    std::cout << "--- Initial Stock ---" << std::endl;
    stockList(fileName);

    
    std::cout << "\n--- Apple price updating ---" << std::endl;
    updatePrice(fileName, "Apple", 5.00);

    
    stockList(fileName);

    
    std::cout << "\n--- Milk deleting ---" << std::endl;
    deleteProduct(fileName, "Milk");


    std::cout << "\n--- Final Stock ---" << std::endl;
    stockList(fileName);

    return 0;
}





void stockList(const std::string& fileName) {
    std::ifstream read(fileName);
    if(!read) {
        std::cerr<<"File could not be opened"<<std::endl;
        return;
    }

    std::string line;
    std::string productName;
    std::string f;
    std::string s;
    int i = 1;
    while(getline(read,line)) {
       
       std::stringstream ss(line);
            getline(ss,productName,',');

            getline(ss,s,',');
            int stock = std::stoi(s);
            
            getline(ss,f,',');
            double price = std::stod(f);
            
              std::cout << i << ") " 
                  << productName 
                  << " | Stock: " << stock 
                  << " | Price: " << price 
                  << std::endl;
    
      i++;
    }
    
    read.close();

}



void addProduct(const std::string& fileName,const std::string& product,double price,int quantity) {
    std::ofstream write(fileName,std::ios::app);
    if(!write) {
        std::cerr<<"[!!File could not be opened!!]"<<std::endl;
        return;
    }

    write<<product<<","<<quantity<<","<<price<<std::endl;


    
    write.close();

}

void deleteProduct(const std::string& fileName,const std::string& target) {
    std::ifstream read(fileName);
    std::ofstream write("temp.txt");
   
    if(!read.is_open() || !write.is_open()) {
        std::cerr<<"File could not be opened"<<std::endl;
        return;
    }

    std::string line;
    while(getline(read,line)) {
        std::stringstream ss(line);
        std::string productName1;
        getline(ss,productName1,',');
        if(productName1 != target) {
            write<<line<<std::endl;
        }
    }
    write.close();
    read.close();
        remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());
}

void updatePrice(const std::string& fileName,const std::string target,double newPrice) {
    std::ofstream write("temp2.txt");
    std::ifstream read(fileName);
    if(!read.is_open() || !write.is_open()) {
        std::cerr<<"File could not be opened"<<std::endl;
        return;
    }
std::string line;
    while(getline(read,line)) {

        std::stringstream ss(line);

        std::string productName, stockStr, priceStr;

        getline(ss, productName, ',');
        getline(ss, stockStr, ',');
        getline(ss, priceStr, ',');

          if(productName == target) {
            write << productName << "," << stockStr << "," << newPrice << std::endl;
        } else {
            write << line << std::endl;
        }
    }
    read.close();
    write.close();
 remove(fileName.c_str());
rename("temp2.txt", fileName.c_str());
}