#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>

void listStock(const std::string& fileName);
void addProduct(const std::string& fileName,const std::string& product,double price,int quantity);
void deleteProduct(const std::string& fileName,const std::string& target);
void updatePrice(const std::string& fileName,const std::string target,double newPrice);

int main() {
    std::string fileName = "stock.txt";
    int choice;

    do {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1) List Stock\n";
        std::cout << "2) Add Product\n";
        std::cout << "3) Delete Product\n";
        std::cout << "4) Update Price\n";
        std::cout << "0) Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if(choice == 1) {
            listStock(fileName);
        }
        else if(choice == 2) {
            std::string product;
            double price;
            int quantity;

            std::cout << "Product name: ";
            std::cin >> product;
            std::cout << "Quantity: ";
            std::cin >> quantity;
            std::cout << "Price: ";
            std::cin >> price;

            addProduct(fileName, product, price, quantity);
        }
        else if(choice == 3) {
            std::string target;
            std::cout << "Product to delete: ";
            std::cin >> target;

            deleteProduct(fileName, target);
        }
        else if(choice == 4) {
            std::string target;
            double newPrice;

            std::cout << "Product name: ";
            std::cin >> target;
            std::cout << "New price: ";
            std::cin >> newPrice;

            updatePrice(fileName, target, newPrice);
        }

    } while(choice != 0);

    return 0;
}



void listStock(const std::string& fileName) {
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
    bool found = false;
    while(getline(read,line)) {
        std::stringstream ss(line);
        std::string productName1;
        getline(ss,productName1,',');
        if(productName1 != target) {
            write<<line<<std::endl;
        }
        else {
            found = true;
        }
    }
    write.close();
    read.close();
    remove(fileName.c_str());
    rename("temp.txt", fileName.c_str());

    if(!found) {
        std::cout << "Product not found!\n";
    }
}

void updatePrice(const std::string& fileName,const std::string target,double newPrice) {
    std::ofstream write("temp2.txt");
    std::ifstream read(fileName);

    if(!read.is_open() || !write.is_open()) {
        std::cerr<<"File could not be opened"<<std::endl;
        return;
    }

    std::string line;
    bool found = false;

    while(getline(read,line)) {

        std::stringstream ss(line);

        std::string productName, stockStr, priceStr;

        getline(ss, productName, ',');
        getline(ss, stockStr, ',');
        getline(ss, priceStr, ',');

        if(productName == target) {
            write << productName << "," << stockStr << "," << newPrice << std::endl;
            found = true;
        } else {
            write << line << std::endl;
        }
    }

    read.close();
    write.close();

    remove(fileName.c_str());
    rename("temp2.txt", fileName.c_str());

    if(!found) {
        std::cout << "Product not found!\n";
    }
}